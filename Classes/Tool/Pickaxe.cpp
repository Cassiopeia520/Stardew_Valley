#include "Pickaxe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

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
    return Tool::init({ "pickaxe", PICKAXE});
}

void Pickaxe::useItem() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    const Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // ��������Ҳ�
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_1, ToolRects::PICKAXE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_2, ToolRects::PICKAXE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_3, ToolRects::PICKAXE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // ����������
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_1, ToolRects::PICKAXE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_2, ToolRects::PICKAXE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_3, ToolRects::PICKAXE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // ��������Ϸ�
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_UP_1, ToolRects::PICKAXE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_UP_2, ToolRects::PICKAXE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // ��������·�
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_1, ToolRects::PICKAXE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_2, ToolRects::PICKAXE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_3, ToolRects::PICKAXE_DOWN_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

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