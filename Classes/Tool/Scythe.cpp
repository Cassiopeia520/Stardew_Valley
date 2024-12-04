#include "Scythe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Scythe* Scythe::create() {
    Scythe* scythe = new (std::nothrow) Scythe();
    if (scythe && scythe->init()) {
        scythe->autorelease();
        return scythe;
    }
    CC_SAFE_DELETE(scythe);
    return nullptr;
}

bool Scythe::init() {
    // ���û���ĳ�ʼ������
    return Tool::init("scythe");
}

void Scythe::useTool() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();
    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // ��������Ҳ�
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_1, ToolRects::SCYTHE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_2, ToolRects::SCYTHE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_3, ToolRects::SCYTHE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // ����������
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_1, ToolRects::SCYTHE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_2, ToolRects::SCYTHE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_3, ToolRects::SCYTHE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // ��������Ϸ�
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_1, ToolRects::SCYTHE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_2, ToolRects::SCYTHE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_3, ToolRects::SCYTHE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // ��������·�
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_1, ToolRects::SCYTHE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_2, ToolRects::SCYTHE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_3, ToolRects::SCYTHE_DOWN_3));
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
