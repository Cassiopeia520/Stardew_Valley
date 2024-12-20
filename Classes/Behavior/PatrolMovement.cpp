/****************************************************************
 * File Function: ѭ���ƶ��ƶ����ʵ�֣����ƾ���ѭ���ƶ���ͬʱ���������������Ӱ��
 * Author:        ����
 ****************************************************************/
#include "PatrolMovement.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ���캯��
PatrolMovement::PatrolMovement(){

}

// ��������
PatrolMovement::~PatrolMovement(){

}

// ��̬��������
PatrolMovement* PatrolMovement::create(const std::vector<Vec2>& patrolPoints, float speed, bool loop){
    PatrolMovement* ret = new (std::nothrow) PatrolMovement();
    if (ret && ret->init(patrolPoints, speed, loop)) {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// ��ʼ��
bool PatrolMovement::init(const std::vector<Vec2>& patrolTrailPoints, float patrolSpeed, bool patrolLoop){
    // ��ʼ��·�����Ƿ�Ϊ��
    if (patrolTrailPoints.empty()) {
        CCLOG("PatrolMovement: patrolPoints is empty!");
        return false;
    }

    // ��ʼ��·������
    patrolPoints= patrolTrailPoints;
    baseSpeed= patrolSpeed;
    loop= patrolLoop;
    currentPointIndex = 0;

    return true;
}

// ִ�ж����ƶ�
void PatrolMovement::execute(Animal* animal){
    // �ж϶���ʵ��
    if (!animal) return;

    // �洢����ĳ�ʼλ��
    initialPosition= animal->getAnimalPosition();

    // ��ʼ�ƶ�����һ��·����
    moveToNextPoint(animal);
}

void PatrolMovement::moveToNextPoint(Animal* animal){
    // �ж϶���ʵ��
    if (!animal) return;

    // �ж�Ѳ��
    if (currentPointIndex >= patrolPoints.size()) {
        if (loop) {
            currentPointIndex = 0;
        }
        else {
            return;     // ��ѭ����Ѳ�߽���
        }
    }

    Vec2 target = patrolPoints[currentPointIndex];
    currentPointIndex++;

    // ��ȡ��ͼ�ߴ磬�����ͼ�ߴ�ͨ��ĳ�ַ�ʽ���ݸ� PatrolMovement
    Size mapSize = Director::getInstance()->getVisibleSize(); // ����Ҫ����ʵ�������ȡ��ͼ�ߴ�

    // ����Ŀ��λ���ڵ�ͼ�߽���
    target = clampPosition(target, mapSize);

    // �����ƶ�ʱ��
    float radius= initialPosition.distance(target);
    float moveDuration =0.0f;

    // ����Ӱ��
    weatherChanged(radius,moveDuration);

    // �����ƶ�����
    auto moveAction = MoveTo::create(moveDuration, target);

    animal->runAction(moveAction);

    // �ƶ���ɺ󣬼���Ѳ��
    auto sequence = Sequence::create(moveAction, CallFunc::create([=]() {
        // �����ƶ�����һ����
        this->moveToNextPoint(animal);
        }), nullptr);
    animal->runAction(sequence);
}

Vec2 PatrolMovement::clampPosition(const Vec2& position, const Size& mapSize)
{
    // �ж��ڵ�ͼ����
    float clampedX = clampf(position.x, 0.0f, FARMMAP_SIZE_WIDTH);
    float clampedY = clampf(position.y, 0.0f, FARMMAP_SIZE_HEIGHT);
    return Vec2(clampedX, clampedY);
}

void PatrolMovement::weatherChanged(float& radius, float& moveDuration){
    // ��ȡ��ǰ����
    DateManage* dateManage = DateManage::getInstance();
    Weather weather = dateManage->getCurrentWeather();

    float speed = 0.0f;

    switch (weather) {
    case Weather::Sunny:
        speed = baseSpeed + SUNNY_SPEED_INFLUENCE; // ������ Constant.h
        break;
    case Weather::LightRain:
        speed = baseSpeed + LIGHTRAIN_SPEED_INFLUENCE;
        break;
    case Weather::HeavyRain:
        speed = baseSpeed + HEAVYRAIN_SPEED_INFLUENCE;
        break;
    case Weather::Snowy:
        speed = 0.0f; // ֹͣ�ƶ�
        break;
    }

    // �����ƶ�ʱ�䣬���ݵ�ǰ�ٶȺ;���
    moveDuration = (speed > 0) ? (radius / speed) : 1.0f; // ȷ������ʱ�䲻Ϊ0
}
