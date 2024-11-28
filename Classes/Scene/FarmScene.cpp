#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"


USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}

	// ��ȡ��Ļ��С��ԭ��
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmSpring11_28.tmx")) {
		return false;
	}
	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(visibleSize.width / 2 -farmMapSize.width / 2, visibleSize.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// ����NPC
	
	Npc* wizard = new Npc("Wizard Yuuu", "Fall 5",
		{ "Magic Essence", "Diamond" },
		{ "Milk" },
		{ "Get out of my way", "How are you?","I like to spend time with you." },
		{ "npcImages/wizard.png" },
		Vec2(origin.x + 420, origin.y + 300));  // ����ͼ��·��

	Npc* cleaner = new Npc("Cleaner Levi", "Winter 25",
		{ "Milk", "Cleaning tools" },
		{ "Clay" },
		{ "...", "Ahh, hi.","Come and have some black-tea with me." },
		{ "npcImages/cleaner.png" },
		Vec2(origin.x + 300, origin.y + 300));
	farmMap->npcInit(Vec2(origin.x + 300, origin.y + 300), wizard);
	farmMap->npcInit(Vec2(origin.x + 370, origin.y + 300), cleaner);

	//����NPC�Ĺ�ϵ
	wizard->setNpcRelation("cleaner", RelationshipStatus::Romance);
	cleaner->setNpcRelation("wizard", RelationshipStatus::Romance);


	// ��ȡ��ҵ�������ӵ�������
	auto player = Player::getInstance();
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); // ��ʼλ��
	this->addChild(player, 3);

	// ��ʾ�������
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
		this->addChild(nameLabel, 4);
	}

	// ��ʼ�����̺���������
	initKeyboardListener();
	initMouseListener();
	return true;
}

void Farm::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.insert(keyCode);
		updateMovement(); // ���ݵ�ǰ���µļ����㷽��
		};

	// �ɿ���ʱ�� keysPressed �Ƴ�
	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.erase(keyCode);
		// ֹͣ����ƶ�
		Player::getInstance()->stopMoving();
		updateMovement(); // ���·���

		};

	// ��Ӽ��������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::updateMovement() {
	Vec2 direction = Vec2::ZERO;

	// ��鰴�����ϣ����ݰ��µļ����㷽��
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) { // ��
		direction.y = 1;
	} 
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) { // ��
		direction.y = -1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) { // ��
		direction.x = -1;
	}
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) { // ��
		direction.x = 1;
	}

	// ��һ�����򣬱���б�����ƶ��ٶȹ���
	if (direction != Vec2::ZERO) {
		direction.normalize();
	}

	// ������Һ͵�ͼ���ƶ�����
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	auto farmDirection = -direction;
	farmMap->moveMapByDirection(farmDirection);
	player->moveByDirection(direction);
}

void Farm::initMouseListener() {
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			Player::getInstance()->useCurrentTool();
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

