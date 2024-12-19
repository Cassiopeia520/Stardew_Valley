#include "WanderMovement.h"
#include "../DateManage/DateManage.h"
#include "../Map/FarmMap.h"
#include "cocos2d.h"

USING_NS_CC;

// ��̬���캯��
WanderMovement* WanderMovement::create(float radius,float interval) {
    WanderMovement* wanderMovement = new (std::nothrow) WanderMovement();
    if (wanderMovement && wanderMovement->init(radius,interval)) {
        return wanderMovement;
    }
    CC_SAFE_DELETE(wanderMovement);
    return nullptr;
}

// ��̬���������ĳ�ʼ��
bool WanderMovement::init(float radius , float interval ) {
    // �ƶ���Χ����
    moveRadius = radius;
    moveInterval = interval;

    return true;
}

// ���캯��
WanderMovement::WanderMovement() {
}

// ��������
WanderMovement::~WanderMovement() {

}

// ִ���ƶ�
void WanderMovement::execute(Animal* animal) {
    // ��ʼ��λ��
    initialPosition = animal->getAnimalPosition();

	// ��ʱ���� performRandomMove
	animal->schedule([=](float dt) {
		this->performRandomMove(animal);
		}, moveInterval,"WanderMovement_Schedule");


}

void WanderMovement::performRandomMove(Animal* animal){
    // ����Ӱ��
    float radius;
    float moveDuration;
    weatherChanged(radius,moveDuration);

    // �������ƫ����
    float angle = CCRANDOM_0_1() * 2 * M_PI; // ����Ƕ�
    float distance = CCRANDOM_0_1() * radius; // �������

    // �����µ�Ŀ��λ��
    Vec2 offset = Vec2(cos(angle), sin(angle)) * distance;
    Vec2 targetPosition = initialPosition + offset;

    // ȷ��Ŀ��λ���ڿɼ���Χ�ڣ���ѡ��
    float mapWidth = 1980.0f;  // ����ʵ�ʵ�ͼ�ߴ����
    float mapHeight = 1080.0f;  // ����ʵ�ʵ�ͼ�ߴ����
    targetPosition.x = clampf(targetPosition.x, 0.0f, mapWidth);
    targetPosition.y = clampf(targetPosition.y, 0.0f, mapHeight);

    auto moveAction = MoveTo::create(moveDuration, targetPosition);

    animal->runAction(moveAction);
}

// ����Ӱ��
void WanderMovement::weatherChanged(float& radius,float& moveDuration) {
    // ��ȡ��ǰ����
    DateManage* dateManage = DateManage::getInstance();
    Weather weather = dateManage->getCurrentWeather();

    switch (weather) {
    case Weather::Sunny:
        radius = moveRadius+SUNNY_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval + SUNNY_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::LightRain:
        radius = moveRadius + LIGHTRAIN_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval +LIGHTRAIN_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::HeavyRain:
        radius = moveRadius + HEAVYRAIN_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval + HEAVYRAIN_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::Snowy:
        radius = 0.0f;
        moveDuration = 0.0f;
    }
}