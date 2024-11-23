#include "NewGameScene.h"
#include "../Player/Player.h"
#include "FarmScene.h"

USING_NS_CC;

// ��ӡ���õı�����Ϣ
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

Scene* NewGame::createScene() {
	return NewGame::create();
}

bool NewGame::init() {
	if (!Scene::init()) {
		return false;
	}

	// ��ȡ��Ļ��С��ԭ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto titleLabel = Label::createWithTTF("Enter Player Name", "fonts/Marker Felt.ttf", 36);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100));
	this->addChild(titleLabel, 1);

	// ���������
	nameInput = ui::TextField::create("Enter Name", "fonts/Marker Felt.ttf", 30);
	nameInput->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));
	nameInput->setMaxLength(15); // �������ֳ���
	nameInput->setMaxLengthEnabled(true);
	nameInput->setTextColor(Color4B::WHITE);
	nameInput->setCursorEnabled(true); // ��ʾ���
	this->addChild(nameInput, 1);

	// ����OK��ť
	auto okButton = ui::Button::create("icon/okButton.png", "icon/okButton.png");
	okButton->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.3));
	okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
	this->addChild(okButton, 1);


	// ������
	auto backItem = MenuItemImage::create(
		"icon/backButton.png",
		"icon/backButton.png",
		CC_CALLBACK_1(NewGame::backCallBack, this));
	if (backItem == nullptr ||
		backItem->getContentSize().width <= 0 ||
		backItem->getContentSize().height <= 0) {
		problemLoading("backItem wrong");
	}
	else {
		// �������½ǵ�λ��
		const float rightPadding = 40;
		const float bottomPadding = 20;
		const float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2 - rightPadding;
		const float y = origin.y + bottomPadding + backItem->getContentSize().height / 2;
		backItem->setPosition(Vec2(x, y));
	}

	// �����˵�����
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	return true;
}

void NewGame::onOKButtonClicked(Ref* pSender) {
	// ��ȡ���������
	std::string playerName = nameInput->getString();
	
	// �������Ϊ�գ�����ΪĬ������
	if (playerName.empty()) {
		playerName = "kuanye";
	}

	// ���������õ�Player������
	Player::getInstance()->setName(playerName);

	// ����FramScene
	auto framScene = Farm::create();
	Director::getInstance()->replaceScene(framScene);
}

void NewGame::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}