#include "FarmScene.h"

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
	
	// ����ũ������Ƭ��ͼ
	auto map = TMXTiledMap::create("Maps/farm.tmx");
	if (map == nullptr) {
		return false;			//��ͼ����ʧ��
	}
	map->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	map->setPosition(origin.x, origin.y);
	this->addChild(map, 0, "Map");

	// �����ͼ��Ϣ
	auto mapSize = map->getContentSize();


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

	// ��ʼ�����̼�����
	initKeyboardListener();

	// ��ʱ�������ڸ��µ�ͼλ��
	schedule([this](float dt) {
		updateMapPosition();
		}, "update_map_position");

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

void Farm::updateMapPosition() {
	auto mapNode = this->getChildByName("Map");
	auto map = dynamic_cast<TMXTiledMap*>(mapNode); // ת��Ϊ TMXTiledMap*
	auto player = Player::getInstance();

	if (!map || !player) {
		return;
	}

	// ��ȡ��ͼ����Ļ�ߴ�
	auto mapSize = map->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// ��ҵ�ǰλ��
	Vec2 playerPos = player->getPosition();

	// �����Ƿ��ˣ������ͼ��ê�������½ǣ������һ���Ϊ�;���һ��������

	float offsetX = playerPos.x - visibleSize.width / 2;
	float offsetY = playerPos.y - visibleSize.height / 2;
	if (offsetX >= (mapSize.width - visibleSize.width) / 2) {
		offsetX = (mapSize.width - visibleSize.width) / 2;
	}
	if (offsetX <= -(mapSize.width - visibleSize.width) / 2) {
		offsetX = -(mapSize.width - visibleSize.width) / 2;
	}
	if (offsetY >= (mapSize.height - visibleSize.height) / 2) {
		offsetY = (mapSize.height - visibleSize.height) / 2;
	}
	if (offsetY <= -(mapSize.height - visibleSize.height) / 2) {
		offsetY = -(mapSize.height - visibleSize.height) / 2;
	}
	const float currentX = -(mapSize.width - visibleSize.width) / 2 - offsetX;
	const float currentY = -(mapSize.height - visibleSize.height) / 2 - offsetY;
	map->setPosition(-(mapSize.width - visibleSize.width) / 2 -offsetX, -(mapSize.height - visibleSize.height) / 2 - offsetY);
}