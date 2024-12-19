#include "Cow.h"
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
	return Cow::initWithFile(COW);
}

// Cow�ࣺ���캯��
Cow::Cow(Vec2 position) :
	Animal(position) {
	milkProduction = 0;
}

// Cow�ࣺ��������
Cow::~Cow() {
}