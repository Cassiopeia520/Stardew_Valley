/****************************************************************
 * File Function: 实现新开始游戏场景类，继承自Scene，从开始场景会切换
 *				  本场景，玩家输入自己的游戏id
 * Author:        赵卓冰
 ****************************************************************/
#include "NewGameScene.h"
#include "../Player/Player.h"
#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../MyButton/MyButton.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* NewGame::createScene() {
	return NewGame::create();
}

bool NewGame::init() {
	if (!Scene::init()) {
		return false;
	}

	// 背景
	auto background = Sprite::create(ResPath::COOP_BACKGROUND);
	if (background) {
		background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
		this->addChild(background, 0);
	}

	// 合作框背景
	auto coopPanel = Sprite::create(ResPath::COOP_PANEL);
	if (coopPanel) {
		coopPanel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
		this->addChild(coopPanel, 1);
	}

	// 输入框背景条
	auto nameBar = Sprite::create(ResPath::NAME_BAR);
	if (nameBar) {
		nameBar->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2 + 80));
		this->addChild(nameBar, 2);
	}

	// 标题标签
	auto titleLabel = Label::createWithTTF("Please Enter Your Name (English or Number).", ResPath::FONT_TTF, 36);
	if (titleLabel) {
		titleLabel->setTextColor(Color4B::BLUE);
		titleLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 150));
		this->addChild(titleLabel, 3);
	}

	// 输入框
	nameInput = ui::TextField::create("Enter Here!", ResPath::FONT_TTF, 30);
	if (nameInput) {
		nameInput->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2 + 80));
		nameInput->setMaxLength(10);
		nameInput->setMaxLengthEnabled(true);
		nameInput->setTextColor(Color4B::WHITE);
		this->addChild(nameInput, 3);
	}

	// OK按钮
	auto okButton = MyButton::create(ResPath::OK_BUTTON, ResPath::OK_BUTTON_ON);
	if (okButton) {
		okButton->setPosition(Vec2(WINSIZE.width * OK_BUTTON_POSITION_X_RATIO,
			WINSIZE.height * OK_BUTTON_POSITION_Y_RATIO));
		okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
		this->addChild(okButton, 3);
	}

	auto backButton = MyButton::create(ResPath::BACK_BUTTON, ResPath::BACK_BUTTON);

	// 返回项
	auto backItem = MenuItemImage::create(ResPath::BACK_BUTTON, ResPath::BACK_BUTTON, CC_CALLBACK_1(NewGame::backCallBack, this));
	if (backItem) {
		const float x = WINSIZE.width - backItem->getContentSize().width / 2 - BACK_BUTTON_PADDING_RIGHT;
		const float y = BACK_BUTTON_PADDING_BOTTOM + backItem->getContentSize().height / 2;
		backItem->setPosition(Vec2(x, y));
	}

	// 菜单容器
	auto menu = Menu::create(backItem, NULL);
	if (menu) {
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 3);
	}

	return true;
}

// OK按钮的回调函数
void NewGame::onOKButtonClicked(Ref* pSender) {
	// 播放音效
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect(ResPath::BUTTON_MUSIC, false, 1.0f, 1.0f, 1.0f);

	// 获取输入的名字
	std::string playerName = nameInput->getString();
	
	// 如果名字为空，设置为默认名字
	if (playerName.empty()) {
		playerName = DEFAULT_PLAYER_NAME;
	}

	// 人物数据设置
	auto player = Player::getInstance();
	player->setPlayerName(playerName);
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);

	// 背包数据设置
	auto bag = Bag::getInstance();

	// 进入FramScene
	auto farmScene = Farm::createScene();
	auto transition = TransitionFade::create(0.5f, farmScene, cocos2d::Color3B::WHITE); // 0.7秒，淡入紫色背景
	Director::getInstance()->replaceScene(transition);
}

// 返回项的回调函数
void NewGame::backCallBack(Ref* pSender) {
	// 播放音效
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect(ResPath::BUTTON_MUSIC, false, 1.0f, 1.0f, 1.0f);

	Director::getInstance()->popScene();
}