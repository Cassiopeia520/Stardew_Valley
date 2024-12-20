/****************************************************************
 * File Function: ʵ�ֿ�ʼ�����࣬�̳���Scene������Ϸ�ĵ�һ������
 * Author:        ��׿��
 ****************************************************************/
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "CooperationScene.h"
#include "NewGameScene.h"
#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../Save/SaveManage.h"
#include "../MyButton/MyButton.h"

USING_NS_CC;

Scene* Welcome::createScene() {
    return Welcome::create();
}

bool Welcome::init() {
    // ����Ƿ��ʼ������
    if (!Scene::init()) {
        return false;
    }

    // ����ͼƬ
    auto background = Sprite::create(ResPath::BACKGROUND_IMAGE);
    if (background) {
        const float x = WINSIZE.width / 2;
        const float y = WINSIZE.height / 2;
        background->setPosition(Vec2(x, y));
    }
    this->addChild(background, -1);     // ��������ӵ�������

    const float baseX = WINSIZE.width / 2;;
    const float baseY = WINSIZE.height / 6;
    auto newGameButton = MyButton::create(ResPath::NEW_GAME_ITEM, ResPath::NEW_GAME_ON_ITEM);
    if (newGameButton) {
        const float x = baseX - 1.5f * (newGameButton->getContentSize().width + MENU_ITEM_INTERVAL);
        const float y = baseY;
        newGameButton->setPosition(Vec2(x, y));
        newGameButton->addClickEventListener(CC_CALLBACK_1(Welcome::menuNewGameCallback, this));
        addChild(newGameButton, 2);
    }

    auto loadGameButton = MyButton::create(ResPath::LOAD_GAME_ITEM, ResPath::LOAD_GAME_ON_ITEM);
    if (loadGameButton) {
        const float x = baseX - 0.5f * (loadGameButton->getContentSize().width + MENU_ITEM_INTERVAL);
        const float y = baseY;
        loadGameButton->setPosition(Vec2(x, y));
        loadGameButton->addClickEventListener(CC_CALLBACK_1(Welcome::menuLoadGameCallback, this));
        addChild(loadGameButton, 2);
    }

    auto cooperationButton = MyButton::create(ResPath::COOPERATION_ITEM, ResPath::COOPERATION_ON_ITEM);
    if (cooperationButton) {
        const float x = baseX + 0.5f * (cooperationButton->getContentSize().width + MENU_ITEM_INTERVAL);
        const float y = baseY;
        cooperationButton->setPosition(Vec2(x, y));
        cooperationButton->addClickEventListener(CC_CALLBACK_1(Welcome::menuCooperationCallback, this));
        addChild(cooperationButton, 2);
    }

    auto closeButton = MyButton::create(ResPath::EXIT_ITEM, ResPath::EXIT_ON_ITEM);
    if (closeButton) {
        const float x = baseX + 1.5f * (closeButton->getContentSize().width + MENU_ITEM_INTERVAL);
        const float y = baseY;
        closeButton->setPosition(Vec2(x, y));
        closeButton->addClickEventListener(CC_CALLBACK_1(Welcome::menuExitCallback, this));
        addChild(closeButton, 2);
    }

    // ��ӭ��ǩ
    auto label = Label::createWithTTF("Welcome!", ResPath::FONT_TTF, 24);
    if (label) {
        label->setPosition(Vec2( + WINSIZE.width / 2,
            WINSIZE.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    // ��������
    auto sprite = Sprite::create(ResPath::TITLE);
    if (sprite) {
        sprite->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 3 * 2));
        this->addChild(sprite, 0);
    }

    return true;
}

// ����Ϸ��ص�����
void Welcome::menuNewGameCallback(cocos2d::Ref* pSender) {
    auto newGameScene = NewGame::createScene();
    auto transition = TransitionFade::create(0.5f, newGameScene, PURPUL); // 0.5�룬������ɫ����
    Director::getInstance()->pushScene(transition);
}

// ������Ϸ��ص�����
void Welcome::menuLoadGameCallback(cocos2d::Ref* pSender) {
    // ���ش浵����
    SaveManage::getInstance()->loadGameData();

    // ����ũ������
    auto farmScene = Farm::createScene();
    auto transition = TransitionFade::create(0.5f, farmScene, cocos2d::Color3B::WHITE); // 0.5�룬�����ɫ����
    Director::getInstance()->pushScene(transition);
}

// ������ص�����
void Welcome::menuCooperationCallback(Ref* pSender) {
    auto cooperationScene = Cooperation::createScene();
    auto transition = TransitionFade::create(0.5f, cooperationScene, PURPUL); // 0.5�룬������ɫ����
    Director::getInstance()->pushScene(transition);
}

// �ر�������ص�����
void Welcome::menuExitCallback(Ref* pSender) {
    // �ر�Ӧ�ó���
    Director::getInstance()->end();
}
