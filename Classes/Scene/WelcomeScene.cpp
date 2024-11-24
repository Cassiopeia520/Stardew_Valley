#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "CooperationScene.h"
#include "NewGameScene.h"
#include "FarmScene.h"

USING_NS_CC;

Scene* Welcome::createScene() {
    return Welcome::create();
}

// ��ӡ���õı�����Ϣ
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

// ��init()�����г�ʼ��ʵ��
bool Welcome::init() {
    // ���ȼ���Ƿ��ʼ������
    if (!Scene::init()) {
        return false;
    }
    // ������ͼ�Ĵ�С������ʹ��1280*720
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    // ԭ������
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // ��ť֮��ļ��
    const float buttonInterval = 24;


    auto background = Sprite::create("icon/background.png");
    if (background == nullptr) {
        problemLoading("'background.png'");
    }
    else {
        // ������ͼƬ����
        const float x = visibleSize.width / 2 + origin.x;
        const float y = visibleSize.height / 2 + origin.y;
        background->setPosition(Vec2(x, y));
        // ��������ӵ������У�zOrderΪ-1ȷ�����������ڵ������
        this->addChild(background, -1);
    }

    // ����Ϸ��
    auto newGameItem = MenuItemImage::create("icon/newGameButton.png", "icon/newGameButton.png", 
        CC_CALLBACK_1(Welcome::menuNewGameCallback, this));
    if (newGameItem == nullptr ||
        newGameItem->getContentSize().width <= 0 ||
        newGameItem->getContentSize().height <= 0) {
        problemLoading("newGameItem wrong");
    }
    else {
        const float x = origin.x + -1.5 * (newGameItem->getContentSize().width + buttonInterval);
        const float y = origin.y;
        newGameItem->setPosition(Vec2(x, y));
    }

    // ������Ϸ��
    auto loadGameItem = MenuItemImage::create("icon/loadGameButton.png", "icon/loadGameButton.png", 
        CC_CALLBACK_1(Welcome::menuLoadGameCallback, this));
    if (loadGameItem == nullptr ||
        loadGameItem->getContentSize().width <= 0 ||
        loadGameItem->getContentSize().height <= 0) {
        problemLoading("loadGameItem wrong");
    }
    else {
        const float x = origin.x + -0.5 * (loadGameItem->getContentSize().width + buttonInterval);
        const float y = origin.y;
        loadGameItem->setPosition(Vec2(x, y));
    }

    // ������
    auto cooperationItem = MenuItemImage::create("icon/cooperationButton.png", "icon/cooperationButton.png", 
        CC_CALLBACK_1(Welcome::menuCooperationCallback, this));
    if (cooperationItem == nullptr ||
        cooperationItem->getContentSize().width <= 0 ||
        cooperationItem->getContentSize().height <= 0) {
        problemLoading("cooperationItem wrong");
    }
    else {
        const float x = origin.x + 0.5 * (cooperationItem->getContentSize().width + buttonInterval);
        const float y = origin.y;
        cooperationItem->setPosition(Vec2(x, y));
    }

    // �˳������һ���Զ��ͷŵĶ���
    auto closeItem = MenuItemImage::create("icon/exitButton.png", "icon/exitButton.png", 
        CC_CALLBACK_1(Welcome::menuExitCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'icon/exitButton.png' and 'icon/exitButton.png'");
    }
    else {
        const float x = origin.x + 1.5 * (closeItem->getContentSize().width + buttonInterval);
        const float y = origin.y;
        closeItem->setPosition(Vec2(x, y));
    }

    // �����˵�����������һ���Զ��ͷŵĶ���
    auto menu = Menu::create(closeItem, NULL);
    menu->addChild(newGameItem);
    menu->addChild(loadGameItem);
    menu->addChild(cooperationItem);

    const float menuX = origin.x + visibleSize.width / 2;
    const float menuY = origin.y + visibleSize.height / 6;
    menu->setPosition(Vec2(menuX, menuY));
    this->addChild(menu, 1);

    // ��������ʼ��һ����ǩ
    auto label = Label::createWithTTF("Welcome!", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add splash screen"
    auto sprite = Sprite::create("icon/title.png");
    if (sprite == nullptr) {
        problemLoading("'icon/title.png'");
    }
    else {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 * 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}

void Welcome::menuNewGameCallback(cocos2d::Ref* pSender) {
    auto newGameScene = NewGame::createScene();
    Director::getInstance()->pushScene(newGameScene);
}

void Welcome::menuLoadGameCallback(cocos2d::Ref* pSender) {
    auto farmScene = Farm::createScene();
    Director::getInstance()->pushScene(farmScene);
}

void Welcome::menuCooperationCallback(Ref* pSender) {
    // Pushһ���³�������ʾ��ϵ��ʽ
    auto cooperationScene = Cooperation::createScene();
    Director::getInstance()->pushScene(cooperationScene);
}

void Welcome::menuExitCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
