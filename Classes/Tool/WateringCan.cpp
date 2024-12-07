#include "WateringCan.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Kettle* Kettle ::create() {
	Kettle *kettle = new(std::nothrow) Kettle();
	if (kettle && kettle->init()) {
		kettle->autorelease();
		return kettle;
	}
	CC_SAFE_DELETE(kettle);
	return nullptr;
}

bool Kettle::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("wateringCan");
}

// Kettle�ࣺ���캯��
Kettle::Kettle() {
	waterLevel = MAX_WATERINGCAN_CAPACITY;
}

// ʹ�ù���
void Kettle::useItem() {
}

// ��õ�ǰˮ�����ˮ��
int Kettle::getCurrentWaterLevel() const {
	return waterLevel;
}

// ���䵱ǰˮ�����ˮ��
void Kettle::refillWateringCan(int water) {
	waterLevel += water;
}