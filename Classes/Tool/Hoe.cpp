#include "Hoe.h"
#include "../Player/Player.h"

USING_NS_CC;

Hoe* Hoe::create() {
	Hoe* hoe = new (std::nothrow) Hoe();
	if (hoe && hoe->init()) {
		hoe->autorelease();
		return hoe;
	}
	CC_SAFE_DELETE(hoe);
}

bool Hoe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("hoe");
}

void Hoe::useTool() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe1.png", Rect(0, 0, 128, 180)));
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe2.png", Rect(0, 0, 169, 184)));
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe3.png", Rect(0, 0, 206, 271)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe1.png", Rect(0, 0, 128, 180)));
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe2.png", Rect(0, 0, 169, 184)));
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe3.png", Rect(0, 0, 206, 271)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe1.png", Rect(0, 0, 89, 190)));
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe2.png", Rect(0, 0, 83, 190)));
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe3.png", Rect(0, 0, 97, 145)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/downUseHoe1.png", Rect(0, 0, 70, 196)));
        frames.pushBack(SpriteFrame::create("tools/hoe/downUseHoe2.png", Rect(0, 0, 70, 195)));
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

	player->runAction(sequence);
}