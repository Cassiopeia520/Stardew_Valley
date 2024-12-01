#include "PickAxe.h"
#include "../Player/Player.h"

USING_NS_CC;

Pickaxe* Pickaxe::create() {
	Pickaxe* pickaxe = new(std::nothrow) Pickaxe();
	if (pickaxe && pickaxe->init()) {
		pickaxe->autorelease();
		return pickaxe;
	}
	CC_SAFE_DELETE(pickaxe);
	return nullptr;
}

bool Pickaxe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("pickaxe");
}

void Pickaxe::useTool() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe1.png", Rect(0, 0, 131, 198)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe2.png", Rect(0, 0, 95, 193)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe3.png", Rect(0, 0, 267, 183)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe1.png", Rect(0, 0, 131, 198)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe2.png", Rect(0, 0, 95, 193)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe3.png", Rect(0, 0, 267, 183)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/upUsePickaxe1.png", Rect(0, 0, 98, 261)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/upUsePickaxe2.png", Rect(0, 0, 93, 146)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe1.png", Rect(0, 0, 86, 270)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe2.png", Rect(0, 0, 81, 203)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe3.png", Rect(0, 0, 63, 132)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe3.png", Rect(0, 0, 69, 131)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standDown.png", Rect(0, 0, 70, 120)));
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