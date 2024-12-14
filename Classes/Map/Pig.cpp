#include "Pig.h"
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