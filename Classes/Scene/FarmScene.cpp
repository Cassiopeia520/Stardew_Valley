#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../DateManage/WeatherManager.h"
#include "../SaveManage/SaveManage.h"

USING_NS_CC;

std::vector<Npc*> Farm::npcs;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	FarmMap* farmMap = FarmMap::getInstance();
	if (!farmMap) {
		return false;
	}

	addChild(farmMap, 0);

	// ��������NPC
	Npc* wizard = Npc::create(WIZARD_INFO);
	Npc* cleaner = Npc::create(CLEANER_INFO);
	npcs.push_back(cleaner);
	npcs.push_back(wizard);
	farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	DialogueBox::isDialogueVisible = false;

	// ���
	auto player = Player::getInstance();
	addChild(player, 3);

	// �������
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", ResPath::FONT_TTF, 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		addChild(nameLabel, 4);
	}

	// ����
	Bag* bag = Bag::getInstance();
	if (bag) {
		addChild(bag, 4);
	}

	// �˳���ť
	auto closeButton = MyButton::create(ResPath::CLOSE_BUTTON_NORMAL, ResPath::CLOSE_BUTTON_HOVER);
	if (closeButton) {
		const auto closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // �������Ͻ�
		addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	Control* control = Control::create();
	addChild(control, 4);

	DateManage* dateManage = DateManage::getInstance();
	addChild(dateManage, 5);

	WeatherManager* weatherManager = WeatherManager::create();
	addChild(weatherManager, 5);

	// ����һ����ʱ����ÿ�����һ�� updateDate ����
	schedule([this, dateManage, farmMap,weatherManager](float deltaTime) {
		dateManage->updateDate();
		farmMap->farmMapUpdateByTime();
		weatherManager->updateWeather(dateManage->getCurrentWeather());
		}, 1.0f, "update_date_key");

	return true;
}

// �رհ�ť�Ļص�����
void Farm::closeButtonClicked(Ref* pSender) {
	SaveManage::getInstance()->saveGameData();
	Director::getInstance()->popScene();
}

Farm::~Farm() {
	npcs.clear();
}