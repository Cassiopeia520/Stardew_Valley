#include "FarmScene.h"

USING_NS_CC;

Scene* Farm::createScene() {
	auto scene = new (std::nothrow) Farm();
	// ���ι���
	if (scene && scene->init()) {
		scene->autorelease();
		return scene;
	}
	else {
		delete scene;
		scene = nullptr;
		return nullptr;
	}
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	// ��ȡ��Ļ��С��ԭ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// ����ũ������Ƭ��ͼ

	auto map = TMXTiledMap::create("Scene/FarmScene.tmx");

	if (map == nullptr) {
		return false;			//��ͼ����ʧ��
	}
	this->addChild(map, 0, 99);

	auto mapSize = map->getContentSize();
	auto winSize = Director::getInstance()->getVisibleSize();

	const float x = winSize.width / 2.0f - mapSize.width / 2.0f;
	const float y = winSize.height / 2.0f - mapSize.height / 2.0f;

	map->setPosition(Vec2(x, y));


	// ��ȡ��ҵ�������ӵ�������
	auto player = Player::getInstance();
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); // ��ʼλ��
	this->addChild(player, 3);

	// ��ʾ�������
	auto nameLabel = Label::createWithTTF(player->getName(), "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
		this->addChild(nameLabel, 2);
	}

	// ��ʼ�����̼�����
	initKeyboardListener();

	return true;
}

void Farm::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 direction = Vec2::ZERO;

		// ���ݰ������÷���
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:  // ��
			direction.y = 1;
			break;
		case EventKeyboard::KeyCode::KEY_S:  // ��
			direction.y = -1;
			break;
		case EventKeyboard::KeyCode::KEY_A:  // ��
			direction.x = -1;
			break;
		case EventKeyboard::KeyCode::KEY_D:  // ��
			direction.x = 1;
			break;
		default:
			break;
		}

		Player::getInstance()->moveByDirection(direction);
		};

	listener->onKeyReleased = [](EventKeyboard::KeyCode KeyCode, Event* event) {
		// ֹͣ����ƶ�
		Player::getInstance()->stopMoving();
		};

	// ��Ӽ��������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}