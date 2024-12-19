#include "Sheep.h"
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
	return Sheep::initWithFile(SHEEP);
}

// ���캯��
Sheep::Sheep(const Vec2& position) :
	Animal(position) {
	woolProduction = 0;
}

// ��������
Sheep::~Sheep() {
}