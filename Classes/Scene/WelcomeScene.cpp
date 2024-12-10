#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "CooperationScene.h"
#include "NewGameScene.h"
#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../SaveManage/SaveManage.h"

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


    // ����Ϸ��
    auto newGameItem = MenuItemImage::create(ResPath::NEW_GAME_ITEM, ResPath::NEW_GAME_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuNewGameCallback, this));
    if (newGameItem) {
        const float x = -1.5 * (newGameItem->getContentSize().width + MENU_ITEM_INTERVAL);
        newGameItem->setPosition(Vec2(x, 0.0f));
    }

    // ������Ϸ��
    auto loadGameItem = MenuItemImage::create(ResPath::LOAD_GAME_ITEM, ResPath::LOAD_GAME_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuLoadGameCallback, this));
    if (loadGameItem) {
        const float x = -0.5 * (loadGameItem->getContentSize().width + MENU_ITEM_INTERVAL);
        loadGameItem->setPosition(Vec2(x, 0.0f));
    }

    // ������
    auto cooperationItem = MenuItemImage::create(ResPath::COOPERATION_ITEM, ResPath::COOPERATION_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuCooperationCallback, this));
    if (cooperationItem) {
        const float x = 0.5 * (cooperationItem->getContentSize().width + MENU_ITEM_INTERVAL);
        cooperationItem->setPosition(Vec2(x, 0.0f));
    }

    // �˳���
    auto closeItem = MenuItemImage::create(ResPath::EXIT_ITEM, ResPath::EXIT_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuExitCallback, this));
    if (closeItem) {
        const float x = 1.5 * (closeItem->getContentSize().width + MENU_ITEM_INTERVAL);
        closeItem->setPosition(Vec2(x, 0.0f));
    }

    // �����˵�����
    auto menu = Menu::create(closeItem, NULL);
    menu->addChild(newGameItem);
    menu->addChild(loadGameItem);
    menu->addChild(cooperationItem);
    const float menuX = WINSIZE.width / 2;
    const float menuY = WINSIZE.height / 6;
    menu->setPosition(Vec2(menuX, menuY));
    this->addChild(menu, 1);

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
