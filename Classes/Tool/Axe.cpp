#include "Axe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
USING_NS_CC;

Axe* Axe::create() {
	Axe* axe = new (std::nothrow) Axe();
	if (axe && axe->init()) {
		axe->autorelease();
		return axe;
	}
	CC_SAFE_DELETE(axe);
	return nullptr;
}

bool Axe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("axe");
}

void Axe::useTool() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // ��������Ҳ�
        frames.pushBack(SpriteFrame::create(ResPath::AXE_RIGHT_1, ToolRects::AXE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_RIGHT_2, ToolRects::AXE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_RIGHT_3, ToolRects::AXE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // ����������
        frames.pushBack(SpriteFrame::create(ResPath::AXE_LEFT_1, ToolRects::AXE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_LEFT_2, ToolRects::AXE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_LEFT_3, ToolRects::AXE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // ��������Ϸ�
        frames.pushBack(SpriteFrame::create(ResPath::AXE_UP_1, ToolRects::AXE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_UP_2, ToolRects::AXE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_UP_3, ToolRects::AXE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // ��������·�
        frames.pushBack(SpriteFrame::create(ResPath::AXE_DOWN_1, ToolRects::AXE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_DOWN_2, ToolRects::AXE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::AXE_DOWN_3, ToolRects::AXE_DOWN_3));
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
    player->runAction(sequence);  // ���Ŷ���
}
