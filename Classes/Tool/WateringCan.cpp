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
	// 调用基类的初始化方法
	return Tool::init("wateringCan");
}

// Kettle类：构造函数
Kettle::Kettle() {
	waterLevel = MAX_WATERINGCAN_CAPACITY;
}

// 使用工具
void Kettle::useItem() {
}

// 获得当前水壶里的水量
int Kettle::getCurrentWaterLevel() const {
	return waterLevel;
}

// 补充当前水壶里的水量
void Kettle::refillWateringCan(int water) {
	waterLevel += water;
}