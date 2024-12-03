#include "NewGameScene.h"
#include "../Player/Player.h"
#include "FarmScene.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Scene* NewGame::createScene() {
	return NewGame::create();
}

bool NewGame::init() {
	if (!Scene::init()) {
		return false;
	}

	// ����
	auto background = Sprite::create(ResPath::COOP_BACKGROUND);
	if (background) {
		background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
		this->addChild(background, 0);
	}

	// �����򱳾�
	auto coopPanel = Sprite::create(ResPath::COOP_PANEL);
	if (coopPanel) {
		coopPanel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
		this->addChild(coopPanel, 1);
	}

	// ����򱳾���
	auto nameBar = Sprite::create(ResPath::NAME_BAR);
	if (nameBar) {
		nameBar->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2 + 80));
		this->addChild(nameBar, 2);
	}

	// �����ǩ
	auto titleLabel = Label::createWithTTF("Please Enter Your Name (English or Number).", ResPath::FONT_TTF, 36);
	if (titleLabel) {
		titleLabel->setTextColor(Color4B::BLUE);
		titleLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 150));
		this->addChild(titleLabel, 3);
	}

	// �����
	nameInput = ui::TextField::create("Enter Here!", ResPath::FONT_TTF, 30);
	if (nameInput) {
		nameInput->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2 + 80));
		nameInput->setMaxLength(10);
		nameInput->setMaxLengthEnabled(true);
		nameInput->setTextColor(Color4B::WHITE);
		this->addChild(nameInput, 3);
	}

	// OK��ť
	auto okButton = ui::Button::create(ResPath::OK_BUTTON, ResPath::OK_BUTTON);
	if (okButton) {
		okButton->setPosition(Vec2(WINSIZE.width * OK_BUTTON_POSITION_X_RATIO,
			WINSIZE.height * OK_BUTTON_POSITION_Y_RATIO));
		okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
		this->addChild(okButton, 3);
	}

	// ������
	auto backItem = MenuItemImage::create(ResPath::BACK_BUTTON, ResPath::BACK_BUTTON, CC_CALLBACK_1(NewGame::backCallBack, this));
	if (backItem) {
		const float x = WINSIZE.width - backItem->getContentSize().width / 2 - BACK_BUTTON_PADDING_RIGHT;
		const float y = BACK_BUTTON_PADDING_BOTTOM + backItem->getContentSize().height / 2;
		backItem->setPosition(Vec2(x, y));
	}

	// �˵�����
	auto menu = Menu::create(backItem, NULL);
	if (menu) {
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 3);
	}

	return true;
}

// OK��ť�Ļص�����
void NewGame::onOKButtonClicked(Ref* pSender) {
	// ��ȡ���������
	std::string playerName = nameInput->getString();
	
	// �������Ϊ�գ�����ΪĬ������
	if (playerName.empty()) {
		playerName = DEFAULT_PLAYER_NAME;
	}

	// ���������õ�Player������
	Player::getInstance()->setPlayerName(playerName);

	// ����FramScene
	auto framScene = Farm::create();
	Director::getInstance()->replaceScene(framScene);
}

// ������Ļص�����
void NewGame::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}