#ifndef __CARROTCROP_H__
#define __CARROTCROP_H__

#include "cocos2d.h"
#include "Crop.h"

/*
 * Class Name:     Carrot
 * Class Function: 胡萝卜作物类
 */
class Carrot : public Crop {
public:
	// 静态创建函数
	static Carrot* create();

	// 初始化
	bool init() override;

	// 构造函数
	Carrot();

	// 生长函数
	void grow() override;

	// 随机产生病害函数
	void generatePest() override;
};


#endif
