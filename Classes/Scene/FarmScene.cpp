#include "FarmScene.h"
#include "../Map/BeachMap.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../DateManage/WeatherManager.h"
#include "../SaveManage/SaveManage.h"

USING_NS_CC;

// ��ͼ�ϵ�npc;
std::vector<Npc*> Farm::npcs;

// ������������̬����
Scene* Farm::createScene() {
	return Farm::create();
}

// ��ʼ��ũ������
bool Farm::init() {
	// ���ȳ�ʼ������
	if (!Scene::init()) {
		return false;
	}

	// ũ����ͼ
	FarmMap* farmMap = FarmMap::getInstance();
	if (farmMap) {
		addChild(farmMap, 0);
	}
	                                                               
	// ����NPC
	Npc* wizard = Npc::create(WIZARD_INFO);
	Npc* cleaner = Npc::create(CLEANER_INFO);
	if (wizard && cleaner) {
		npcs.push_back(cleaner);
		npcs.push_back(wizard);
		farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
		farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	}

	// ���
	auto player = Player::getInstance();
	if (player) {
		addChild(player, 3);
	}
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);

	// ������ֱ�ǩ
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
		const Size closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // �������Ͻ�
		addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	// �������ͼ��̵Ľ���
	Control* farmControl = Control::create(farmMap);
	if (farmControl) {
		addChild(farmControl, 4, "farm_control");
	}

	// ���ڹ���
	DateManage* dateManage = DateManage::getInstance();
	if (dateManage) {
		addChild(dateManage, 5);
	}

	// ��������
	WeatherManager* weatherManager = WeatherManager::create();
	if (weatherManager) {
		addChild(weatherManager, 5);
	}

	// ������ʱ����ÿ�����һ�� updateDate ����
	schedule([this, dateManage, farmMap,weatherManager](float deltaTime) {
		dateManage->updateDate();
		farmMap->mapUpdateByTime();
		weatherManager->updateWeather(dateManage->getCurrentWeather());
		}, 5.0f, "update_date_key");

	// ÿ֡����Ƿ�Ҫ�л�����
	schedule([this](float dt) {
		this->changeSceneAuto();
		}, "change_scene");

	return true;
}

// �رհ�ť�Ļص�����
void Farm::closeButtonClicked(Ref* pSender) {
	SaveManage::getInstance()->saveGameData();
	Director::getInstance()->popScene();
}

// ������������ֹnpcs�д���Ұָ��
Farm::~Farm() {
	npcs.clear();
}

// ���������λ���Զ���ũ�������л��������ĸ�����
void Farm::changeSceneAuto() {
	// ���������ڵ�ͼ�е�λ��
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	const auto positionInMap = player->getPosition() - farmMap->getPosition();

	// ����ĳ���
	const auto playerDirection = player->getLastDirection();

	// ���������±߽�
	if (playerDirection == Vec2(0, -1) && positionInMap.y < CHANGE_MAP_DISTANCE && !(getChildByName("beach_map"))) {
		// �Ƴ���ũ���Ŀ���
		removeChildByName("farm_control");
		auto beachMap = BeachMap::getInstance();

		// ��Ӷ�ɳ̲�Ŀ���
		Control* beachControl = Control::create(beachMap);
		if (beachControl) {
			addChild(beachControl, 5, "beach_control");
		}
		addChild(beachMap, 1, "beach_map");

		// ��������±߽�ת�Ƶ��ϱ߽�
		const float newPlayerPosX = player->getPositionX();
		const float newPlayerPosY = WINSIZE.height - player->getPositionY();
		player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
	}

	// ��ǰ�Ǻ�̲����
	if ((getChildByName("beach_map"))) {
		auto beachMap = BeachMap::getInstance();
		const auto positionInBeachMap = player->getPosition() - beachMap->getPosition();

		// ������������ϱ߽�
		if (playerDirection == Vec2(0, 1) && positionInMap.y > WINSIZE.height - CHANGE_MAP_DISTANCE) {
			removeChildByName("beach_control");
			removeChildByName("beach_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// ��������ϱ߽�ת�Ƶ��±߽�
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}
}
