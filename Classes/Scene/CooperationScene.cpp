#include "CooperationScene.h"
#include "SimpleAudioEngine.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Scene* Cooperation::createScene() {
    return Cooperation::create();
}

bool Cooperation::init() {
    if (!Scene::init()) {
        return false;
    }

    // ����
    auto background = Sprite::create(ResPath::COOP_BACKGROUND);
    if (background) {
        background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
        this->addChild(background, 0); // ������ z-order ���
    }

    // ������
    auto coopPanel = Sprite::create(ResPath::COOP_PANEL);
    if (coopPanel) {
        coopPanel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
        this->addChild(coopPanel, 1);
    }

    // ������ʾ
    coopText = Label::createWithTTF(COOP_TEXT_CONTENT, ResPath::FONT_TTF, 24);
    if (coopText) {
        const Vec2 textPosition = Vec2(WINSIZE.width / 2, WINSIZE.height / 2); // ��������λ�ã�ʹ��λ����Ļ����
        coopText->setPosition(textPosition);
        this->addChild(coopText, 2);
    }

    // ������
    auto backItem = MenuItemImage::create(
        ResPath::BACK_BUTTON,                               // ���ذ�ť����ͨ״̬ͼƬ
        ResPath::BACK_BUTTON,                               // ���ذ�ť�İ���״̬ͼƬ
        CC_CALLBACK_1(Cooperation::backCallBack, this));    // ����ص�����
    if (backItem) {
        const float x = WINSIZE.width - backItem->getContentSize().width / 2 - BACK_BUTTON_PADDING_RIGHT;
        const float y = BACK_BUTTON_PADDING_BOTTOM + backItem->getContentSize().height / 2;
        backItem->setPosition(Vec2(x, y));
    }

    // �˵�����
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);

    // ���·���İ�ť
    auto upButton = MenuItemImage::create(
        ResPath::UP_ARROW,
        ResPath::UP_ARROW,
        CC_CALLBACK_1(Cooperation::onUpButtonClicked, this));
    auto downButton = MenuItemImage::create(
        ResPath::DOWN_ARROW,
        ResPath::DOWN_ARROW,
        CC_CALLBACK_1(Cooperation::onDownButtonClicked, this));

    // ��ť�������Ҳ�
    if (upButton && downButton) {
        upButton->setPosition(Vec2(WINSIZE.width - ARROW_BUTTON_PADDING, WINSIZE.height / 2 + UP_BUTTON_OFFSET_Y));
        downButton->setPosition(Vec2(WINSIZE.width - ARROW_BUTTON_PADDING, WINSIZE.height / 2 + DOWN_BUTTON_OFFSET_Y));
    }

    // ��ť�˵�
    auto buttonMenu = Menu::create(upButton, downButton, NULL);
    if (buttonMenu) {
        buttonMenu->setPosition(Vec2::ZERO);
        this->addChild(buttonMenu, 4);
    }

    return true;
}

// ���ذ�ť�ص�����
void Cooperation::backCallBack(Ref* pSender) {
    Director::getInstance()->popScene(); // ������һ������
}

// ���ϰ�ť�ص�����
void Cooperation::onUpButtonClicked(Ref* pSender) {
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, -MOVE_BY_DISTANCE)); // �����ƶ�ָ������
        coopText->runAction(moveBy);                                    // ִ�ж���
    }
}

// ���°�ť�ص�����
void Cooperation::onDownButtonClicked(Ref* pSender) {
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, MOVE_BY_DISTANCE));  // �����ƶ�ָ������
        coopText->runAction(moveBy);                                    // ִ�ж���
    }
}