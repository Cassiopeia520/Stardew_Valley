#include "Axe.h"
#include "../Player/Player.h"

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
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/axe/rightUseAxe1.png", Rect(0, 0, 100, 183)));
        frames.pushBack(SpriteFrame::create("tools/axe/rightUseAxe2.png", Rect(0, 0, 201, 183)));
        frames.pushBack(SpriteFrame::create("tools/axe/rightUseAxe3.png", Rect(0, 0, 165, 164)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/axe/leftUseAxe1.png", Rect(0, 0, 100, 183)));
        frames.pushBack(SpriteFrame::create("tools/axe/leftUseAxe2.png", Rect(0, 0, 201, 183)));
        frames.pushBack(SpriteFrame::create("tools/axe/leftUseAxe3.png", Rect(0, 0, 165, 164)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/axe/upUseAxe1.png", Rect(0, 0, 85, 200)));
        frames.pushBack(SpriteFrame::create("tools/axe/upUseAxe2.png", Rect(0, 0, 81, 127)));
        frames.pushBack(SpriteFrame::create("tools/axe/upUseAxe3.png", Rect(0, 0, 75, 145)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/axe/downUseAxe1.png", Rect(0, 0, 74, 185)));
        frames.pushBack(SpriteFrame::create("tools/axe/downUseAxe2.png", Rect(0, 0, 75, 127)));
        frames.pushBack(SpriteFrame::create("tools/downUseAxe3.png", Rect(0, 0, 77, 109)));
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
