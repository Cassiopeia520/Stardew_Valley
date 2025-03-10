/****************************************************************
 * File Function: 实现锄头类，继承自Tool，用来锄地
 * Author:        韦瑾钰 赵卓冰
 ****************************************************************/
#include "Hoe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 静态初始化方法
Hoe* Hoe::create() {
	Hoe* hoe = new (std::nothrow) Hoe();
	if (hoe && hoe->init()) {
		hoe->autorelease();
		return hoe;
	}
	CC_SAFE_DELETE(hoe);
    return nullptr;
}

// 初始化斧头
bool Hoe::init() {
	// 调用基类的初始化方法
    return Tool::init({ "hoe", HOE});
}

// 使用工具
void Hoe::useItem() {
    // 获取玩家实例
    Player* player = Player::getInstance();

    // 创建动画帧
    Vector<SpriteFrame*> frames;
    const Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // 玩家面向右侧
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_1, ToolRects::HOE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_2, ToolRects::HOE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_3, ToolRects::HOE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // 玩家面向左侧
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_1, ToolRects::HOE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_2, ToolRects::HOE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_3, ToolRects::HOE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // 玩家面向上方
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_1, ToolRects::HOE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_2, ToolRects::HOE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_3, ToolRects::HOE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // 玩家面向下方
        frames.pushBack(SpriteFrame::create(ResPath::HOE_DOWN_1, ToolRects::HOE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_DOWN_2, ToolRects::HOE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            }),
            nullptr
            );

	player->runAction(sequence);
}