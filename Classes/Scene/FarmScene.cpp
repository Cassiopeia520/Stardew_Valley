/****************************************************************
 * File Function: ʵ��ũ�������࣬�̳���Scene������Ϸ����Ҫ����
 *				  ũ������npc����ҿ��Ը��֣���ֳ�����㣬���������׵ȡ�
 * Author:        ��׿��
 ****************************************************************/
#include "FarmScene.h"
#include "../Map/BeachMap.h"
#include "../Map/CaveMap.h"
#include "../Map/ForestMap.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../Weather/WeatherManager.h"
#include "../Save/SaveManage.h"
#include "../Npc/NoticeBoard.h"
#include "../Item/ItemFactory.h"

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

// ��ȡ��ͼ�����е�npc
std::vector<Npc*> Farm::getNpcs(){
	return npcs;
}

// ���������λ���Զ���ũ�������л��������ĸ�����
void Farm::changeSceneAuto() {
	// ���������ڵ�ͼ�е�λ��
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	const auto positionInMap = player->getPosition() - farmMap->getPosition();
	const auto farmMapSize = farmMap->getMapSize();

	// ����ĳ���
	const auto playerDirection = player->getLastDirection();

	// ��ǰ��ũ����ͼ
	if (getChildByName("farm_control")) {
		// ��������ͬ�ı߽���벻ͬ���µ�ͼ
		if (playerDirection == Vec2(0, -1) && positionInMap.y < CHANGE_MAP_DISTANCE) {
			// �Ƴ���ũ���Ŀ���
			removeChildByName("farm_control");

			// ��Ӷ�ɳ̲�Ŀ���
			auto beachMap = BeachMap::getInstance();
			if (beachMap) {
				addChild(beachMap, 1, "beach_map");
				Control* beachControl = Control::create(beachMap);
				if (beachControl) {
					addChild(beachControl, 5, "beach_control");
					// ������̲����¹������
					auto bag = Bag::getInstance();
					// ���������û����ͣ����ù������
					if (!bag->checkItemIn("fishingRod")) {
						auto fishingRod = ItemFactory::createItem("fishingRod");
						bag->addItem(fishingRod);
					}
				}
			}

			// ��������±߽�ת�Ƶ�ɳ̲��ͼ���ϱ߽磬ʵ��ƽ������
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
		else if (playerDirection == Vec2(0, 1) && positionInMap.y > farmMapSize.height - CHANGE_MAP_DISTANCE) {
			// �Ƴ���ũ���Ŀ���
			removeChildByName("farm_control");

			// ��ӶԶ�Ѩ�Ŀ���
			auto caveMap = CaveMap::getInstance();
			if (caveMap) {
				addChild(caveMap, 1, "cave_map");
				Control* caveControl = Control::create(caveMap);
				if (caveControl) {
					addChild(caveControl, 5, "cave_control");

					// ������Ѩ����¹���ʮ�ָ�
					auto bag = Bag::getInstance();
					if (!bag->checkItemIn("pickaxe")) {
						auto pickaxe = ItemFactory::createItem("pickaxe");
						bag->addItem(pickaxe);
					}
					// ��������±߽�ת�Ƶ���Ѩ��ͼ���±߽磬ʵ��ƽ������
					const float newPlayerPosX = player->getPositionX();
					const float newPlayerPosY = CHANGE_MAP_DISTANCE;
					player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
				}
			}

		}
		else if (playerDirection == Vec2(1, 0) && positionInMap.x > farmMapSize.width - CHANGE_MAP_DISTANCE) {
			// �Ƴ���ũ���Ŀ���
			removeChildByName("farm_control");

			// ��Ӷ�ɭ�ֵĿ���
			auto forestMap = ForestMap::getInstance();
			if (forestMap) {
				addChild(forestMap, 1, "forest_map");
				Control* forestControl = Control::create(forestMap);
				if (forestControl) {
					addChild(forestControl, 5, "forest_control");
					// ��������±߽�ת�Ƶ���Ѩ��ͼ���±߽磬ʵ��ƽ������
					const float newPlayerPosX = CHANGE_MAP_DISTANCE;
					const float newPlayerPosY = player->getPositionY();
					player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
				}
			} 
		}


	}

	// ��ǰ�Ǻ�̲��ͼ
	if (getChildByName("beach_control")) {
		auto beachMap = BeachMap::getInstance();
		const auto positionInBeachMap = player->getPosition() - beachMap->getPosition();
		const auto beachMapSize = beachMap->getMapSize();
		// ������������ϱ߽�
		if (playerDirection == Vec2(0, 1) && positionInBeachMap.y > beachMapSize.height - 2 * CHANGE_MAP_DISTANCE) {
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

	// ��ǰ�Ƕ�Ѩ��ͼ
	if (getChildByName("cave_control")) {
		auto caveMap = CaveMap::getInstance();
		const auto positionInCaveMap = player->getPosition() - caveMap->getPosition();

		// ������������±߽�
		if (playerDirection == Vec2(0, -1) && positionInCaveMap.y < CHANGE_MAP_DISTANCE) {
			removeChildByName("cave_control");
			removeChildByName("cave_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// ��������±߽�ת�Ƶ��ϱ߽�
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}

	// ��ǰ��ɭ�ֵ�ͼ
	if (getChildByName("forest_control")) {
		auto forestMap = ForestMap::getInstance();
		const auto positionInForestMap = player->getPosition() - forestMap->getPosition();

		// �������������߽�
		if (playerDirection == Vec2(-1, 0) && positionInForestMap.x < CHANGE_MAP_DISTANCE) {
			removeChildByName("forest_control");
			removeChildByName("forest_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// ���������߽�ת�Ƶ��ұ߽�
			const float newPlayerPosX = WINSIZE.width - CHANGE_MAP_DISTANCE;
			const float newPlayerPosY = player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}
}

