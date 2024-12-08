#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "Tool.h"
#include "../Constant/Constant.h"

// 水壶类
class Kettle : public Tool {
private:

	// 水壶的含水量
	int waterLevel;

public:
	// 静态创建方法
	static Kettle* create();

	// 水壶的构造函数
	Kettle();

	// 初始化水壶
	bool init();

	// 使用工具
	void useItem() override;

	// 获得当前水壶里的水量
	int Kettle::getCurrentWaterLevel() const;

	// 补充当前水壶里的水量
	void Kettle::refillWateringCan(int water);
};

#endif