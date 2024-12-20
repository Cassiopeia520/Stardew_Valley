/****************************************************************
 * File Function: ʵ��ˮ���࣬�̳���Tool��
 * Author:        Τ��� ����
 ****************************************************************/
#include "Kettle.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// Kettle�ࣺ��̬��������
Kettle* Kettle ::create() {
	Kettle *kettle = new(std::nothrow) Kettle();
	if (kettle && kettle->init()) {
		kettle->autorelease();
		return kettle;
	}
	CC_SAFE_DELETE(kettle);
	return nullptr;
}

// ��ʼ��ˮ��
bool Kettle::init() {
	// ���û���ĳ�ʼ������
    return Tool::init({"kettle", KETTLE});
}

// ��õ�ǰˮ�����ˮ��
int Kettle::getCurrentWaterLevel() const {
    return waterLevel;
}

// ���䵱ǰˮ�����ˮ��
void Kettle::refillWateringCan(int water) {
    waterLevel += water;
}

// Kettle�ࣺ���캯��
Kettle::Kettle() {
	waterLevel = MAX_WATERINGCAN_CAPACITY;
}

// ʹ�ù���
void Kettle::useItem() {
    // ��ȡ���ʵ��
    Player* player = Player::getInstance();

    // ��������֡
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // ��������Ҳ�
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_1, ToolRects::KETTLE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_2, ToolRects::KETTLE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_3, ToolRects::KETTLE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_4, ToolRects::KETTLE_RIGHT_4));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_5, ToolRects::KETTLE_RIGHT_5));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // ����������
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_1, ToolRects::KETTLE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_2, ToolRects::KETTLE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_3, ToolRects::KETTLE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_4, ToolRects::KETTLE_LEFT_4));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_5, ToolRects::KETTLE_LEFT_5));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // ��������Ϸ�
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_1, ToolRects::KETTLE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_2, ToolRects::KETTLE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_3, ToolRects::KETTLE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_4, ToolRects::KETTLE_UP_4));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // ��������·�
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_1, ToolRects::KETTLE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_2, ToolRects::KETTLE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_3, ToolRects::KETTLE_DOWN_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // ÿ֡���� 0.1 ��
    auto animate = Animate::create(animation);

    // �������У����Ŷ�����ִ�ж�����߼�
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            }),
            nullptr
            );
    player->runAction(sequence);  // ���Ŷ���

    // ����ˮ�����ˮ
    if (waterLevel >= AMOUNT_OF_WATER_PER_USE) {
        waterLevel -= AMOUNT_OF_WATER_PER_USE;
    }
}