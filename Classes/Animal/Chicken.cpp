#include "Chicken.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/PatrolMovement.h"
#include "../Behavior/WanderMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ��̬��Ա���������ڴ���������һ���µ�Chicken���Ͷ����ʵ��
Chicken* Chicken::create(const Vec2& position) {
	Chicken* chicken = new (std::nothrow) Chicken(position);
	if (chicken && chicken->init()) {
		chicken->autorelease();
		return chicken;
	}

	CC_SAFE_DELETE(chicken);
	return nullptr;
}
   
// ��ʼ������
bool Chicken::init() {
	// ��������·��
	Vec2 position = getAnimalPosition();
	std::vector<Vec2> patrolPoints = {
	   Vec2(position.x, position.y),
	   Vec2(position.x + PATROL_OFFSET, position.y),
	   Vec2(position.x + PATROL_OFFSET, position.y +PATROL_OFFSET),
	   Vec2(position.x, position.y +PATROL_OFFSET)
	};

	// ����������Ѳ���ƶ���Ϊ
	PatrolMovement* patrolMovement = PatrolMovement::create(patrolPoints, 100.0f, true);
	if (patrolMovement) {
		setMovementBehavior(patrolMovement);
	}

	return Chicken::initWithFile(CHICKEN);
}

// ���캯��
Chicken::Chicken(const Vec2& position) :
	Animal(position){
	eggCount = 0;
}

// ��������
Chicken::~Chicken() {

}

// �����ƶ���Ϊ
void Chicken::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<PatrolMovement*>(behavior)->execute(this);
	}
}