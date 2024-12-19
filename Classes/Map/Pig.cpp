#include "Pig.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/WanderMovement.h"
#include "../Behavior/PatrolMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ��̬��Ա���������ڴ���������һ���µ�Sheep���Ͷ����ʵ��
Pig* Pig::create(const Vec2& position) {
	Pig* pig = new (std::nothrow) Pig(position);
	if (pig && pig->init()) {
		pig->autorelease();
		return pig;
	}

	CC_SAFE_DELETE(pig);
	return nullptr;
}

// ��ʼ������
bool Pig::init() {
	// �������·��
	Vec2 position = getAnimalPosition();
	std::vector<Vec2> patrolPoints = {
		Vec2(position.x, position.y),												// ��һ����
		Vec2(position.x + PATROL_OFFSET, position.y),								// �ڶ�����
		Vec2(position.x + PATROL_OFFSET/2, position.y + sin(M_PI/3)*(PATROL_OFFSET))				// �������㣨��Ϊ50 * sin(60��) �� 43.3��
	};

	// ����������Ѳ���ƶ���Ϊ
	PatrolMovement* patrolMovement = PatrolMovement::create(patrolPoints, 100.0f, true);
	if (patrolMovement) {
		setMovementBehavior(patrolMovement);
	}

	return Pig::initWithFile(PIG);
}

// ���캯��
Pig::Pig(const Vec2& position) :
	Animal(position) {
	truffleCount = 0;
}

// ��������
Pig::~Pig() {
}

// ��ȡ��¶����
int Pig::getTruffleCount() const {
	return truffleCount;
}

// �����ƶ���Ϊ
void Pig::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<PatrolMovement*>(behavior)->execute(this);
	}
}