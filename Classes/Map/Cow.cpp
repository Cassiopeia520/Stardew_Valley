#include "cocos2d.h"
#include "Cow.h"
#include "FarmMap.h"
#include "../Behavior/WanderMovement.h"
#include "../Behavior/MovementBehavior .h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ��̬����������������Cow����
Cow* Cow::create(Vec2 position) {
	Cow* cow = new (std::nothrow) Cow(position);
	if (cow && cow->init()) {
		cow->autorelease();
		return cow;
	}
	CC_SAFE_DELETE(cow);
	return nullptr;
}

// ��ʼ������
bool Cow::init(){
    // ANIMAL��ʼ��
    if (!Animal::initWithFile(COW)) {
        return false;
    }

    // ����ţ���ƶ���Ϊ
    movementBehavior = WanderMovement::create(COW_MOVE_RADIUS,COW_MOVE_INTERVAL);

    // �����ƶ�����
    setMovementBehavior(movementBehavior);

    return true;
}

// Cow�ࣺ���캯��
Cow::Cow(Vec2 position) :
	Animal(position) {
	milkProduction = 0;
}

// Cow�ࣺ��������
Cow::~Cow() {

}

// �����ƶ���Ϊ
void Cow::setMovementBehavior(MovementBehavior* behavior){
    if (behavior) {
        dynamic_cast<WanderMovement*>(behavior)->execute(this);
    }
}