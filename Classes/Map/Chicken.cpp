#include "Chicken.h"
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