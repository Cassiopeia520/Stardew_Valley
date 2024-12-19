#include "Sheep.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/PatrolMovement.h"
#include "../Behavior/WanderMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ��̬��Ա���������ڴ���������һ���µ�Sheep���Ͷ����ʵ��
Sheep* Sheep::create(const Vec2& position) {
	Sheep* sheep = new (std::nothrow) Sheep(position);
	if (sheep && sheep->init()) {
		sheep->autorelease();
		return sheep;
	}

	CC_SAFE_DELETE(sheep);
	return nullptr;
}

// ��ʼ������
bool Sheep::init() {
	// ANIMAL��ʼ��
	if (!Animal::initWithFile(SHEEP)) {
		return false;
	}

	// �����ƶ���Ϊ
	movementBehavior = WanderMovement::create(SHEEP_MOVE_RADIUS, SHEEP_MOVE_INTERVAL);

	// �����ƶ�����
	setMovementBehavior(movementBehavior);

	return true;
}

// ���캯��
Sheep::Sheep(const Vec2& position) :
	Animal(position) {
	woolProduction = 0;
}

// ��������
Sheep::~Sheep() {

}

// �����ƶ���Ϊ
void Sheep::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<WanderMovement*>(behavior)->execute(this);
	}
}