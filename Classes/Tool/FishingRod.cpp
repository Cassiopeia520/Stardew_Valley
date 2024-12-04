#include "FishingRod.h"
#include "../Player/Player.h"
#include "../Scene/FarmScene.h" 
#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool FishingRod::isUsed = false;

FishingRod* FishingRod::create() {
	FishingRod* fishingRod = new (std::nothrow) FishingRod();
	if (fishingRod && fishingRod->init()) {
		fishingRod->autorelease();
		return fishingRod;
	}
	CC_SAFE_DELETE(fishingRod);
	return nullptr;
}

bool FishingRod::init()
{
    // ���û���ĳ�ʼ������
    return Tool::init("fishingRod");
}

void FishingRod::useTool()
{
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();

    // �����ӳ���͵Ķ���
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_1, ToolRects::FISHING_OUT_1));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_2, ToolRects::FISHING_OUT_2));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_3, ToolRects::FISHING_OUT_3));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_4, ToolRects::FISHING_OUT_4));

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // ÿ֡���� 0.1 ��
    auto animate = Animate::create(animation);

    // �������У����Ŷ�����ִ�ж�����߼�
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            // ��������֡
            Vector<SpriteFrame*> framesWaiting;

            Vec2 direction = player->getLastDirection();

            // �����ӳ���͵Ķ���
            framesWaiting.pushBack(SpriteFrame::create(ResPath::FISHING_WAITING_1, ToolRects::FISHING_WAITING_1));
            framesWaiting.pushBack(SpriteFrame::create(ResPath::FISHING_WAITING_2, ToolRects::FISHING_WAITING_2));

            auto animationWaiting = Animation::createWithSpriteFrames(framesWaiting, 0.5f);
            animationWaiting->setLoops(-1);
            auto animateWait = Animate::create(animationWaiting);

            player->runAction(animateWait);
            }),

            nullptr
            );

    if (isUsed == true) {
        player->stopAllActions(); // ֹͣ��������
        this->reelInRod();      // �����ջض���
        isUsed = false;
    }
    else {
        player->runAction(sequence);
        isUsed = true;
    }
}

void FishingRod::reelInRod()
{
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_IN_1, ToolRects::FISHING_IN_1));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_IN_2, ToolRects::FISHING_IN_2));
    frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // ÿ֡���� 0.1 ��
    auto animate = Animate::create(animation);

    // �������У����Ŷ�����ִ�ж�����߼�
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            // todo: ��������߼����������Ƿ�����Ŀ��
            }),
            nullptr
            );
    player->runAction(sequence);  // ���Ŷ���
}
