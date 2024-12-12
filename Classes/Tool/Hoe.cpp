#include "Hoe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Hoe* Hoe::create() {
	Hoe* hoe = new (std::nothrow) Hoe();
	if (hoe && hoe->init()) {
		hoe->autorelease();
		return hoe;
	}
	CC_SAFE_DELETE(hoe);
    return nullptr;
}

bool Hoe::init() {
	// ���û���ĳ�ʼ������
    return Tool::init({ "hoe", HOE});
}

void Hoe::useItem() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();

    // ��������֡
    Vector<SpriteFrame*> frames;
    const Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // ��������Ҳ�
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_1, ToolRects::HOE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_2, ToolRects::HOE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_RIGHT_3, ToolRects::HOE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // ����������
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_1, ToolRects::HOE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_2, ToolRects::HOE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_LEFT_3, ToolRects::HOE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // ��������Ϸ�
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_1, ToolRects::HOE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_2, ToolRects::HOE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_UP_3, ToolRects::HOE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // ��������·�
        frames.pushBack(SpriteFrame::create(ResPath::HOE_DOWN_1, ToolRects::HOE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::HOE_DOWN_2, ToolRects::HOE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // ÿ֡���� 0.1 ��
    auto animate = Animate::create(animation);

    // �������У����Ŷ�����ִ�ж�����߼�
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            //CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
            // todo: ��������߼����������Ƿ�����Ŀ��
            }),
            nullptr
            );

	player->runAction(sequence);
}