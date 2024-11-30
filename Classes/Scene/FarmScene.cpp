#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Constant/Constant.h"


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


	// ���� NPC ʾ��
	Npc* wizard = new Npc(WIZARD);
	Npc* cleaner = new Npc(CLEANER);

	//���ԣ����ܶ�90
	cleaner->increaseFriendship(90);
	npcs.push_back(cleaner);
	npcs.push_back(wizard);

	farmMap->npcInit(Vec2(origin.x + 300, origin.y + 300), wizard);
	farmMap->npcInit(Vec2(origin.x + 500, origin.y + 300), cleaner);
	isDialogueVisible = false;

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

	//��ʾ�Ի���,�������¼�������
	initMouseListener();
}

void Farm::showDialogue(Npc* npc) {

	if (isDialogueVisible) {
		return;  // ����Ի����Ѿ���ʾ��������ʾ
	}
	// ��ȡ��Ļ�ߴ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Player* player = Player::getInstance();
	// ��ȡ��ҵ�λ��
	auto playerPosition = player->getPosition();

	// �����Ի��򱳾�ͼƬ
	auto dialogueBackground = Sprite::create("npcImages/dialogueBox.png");
	if (!dialogueBackground) {
		return;
	}

	// �������ִ�С
	const float padding = 20.0f;  // ���������ֵļ��
	auto label = Label::createWithTTF(npc->printDialogue(), "fonts/Marker Felt.ttf", 44);

	// �������ֵĿ�Ⱥ͸߶ȣ�ȷ�������ܹ���������
	const float labelWidth = 720;  // ����ռ���
	const float labelHeight = 390;  // ����ռ�߶�

	// ����������Ĵ�С
	dialogueBackground->setContentSize(Size(1283, 462));//�زĿ��С
	// ���öԻ��򱳾���λ��
	dialogueBackground->setPosition(Vec2(640, 200));//ʹ�Ի�������Ļ�°��ռ��
	this->addChild(dialogueBackground, 10);  // ȷ������ͼ�����ϲ�

	// �������ֵ�λ�úͶ��뷽ʽ
	label->setDimensions(labelWidth - 50, labelHeight - 50);  // ���ֿ�Ŀ��Ϊ������Ŀ�ȣ����ø߶�Ϊ������߶�,��΢��С
	label->setPosition(Vec2(dialogueBackground->getPositionX() - 240,
		dialogueBackground->getPositionY()));
	label->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);  // �������϶���
	label->setTextColor(Color4B::WHITE);  // ����������ɫΪ��ɫ
	this->addChild(label, 11);  // ȷ�������ڱ���ͼ֮��

	//�����������
	std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png"; 

	// ��������ʾNPC������
	auto npcTalkImage = Sprite::create(npcImageName);
	if (npcTalkImage) {
		npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));  // ����ͼƬ��ʾ��λ��
		this->addChild(npcTalkImage, 12);  // ȷ��ͼ�������ϲ�
	}

	//�ڶԻ����������������
	auto nameLabel = Label::createWithTTF(npc->getNpcName(), "fonts/Marker Felt.ttf", 40);

	nameLabel->setPosition(Vec2(dialogueBackground->getPositionX() + 360, dialogueBackground->getPositionY() - 140));

	nameLabel->setTextColor(Color4B::WHITE);  // ����������ɫΪ��ɫ
	this->addChild(nameLabel, 11);  // ȷ�������ڱ���ͼ֮��
	isDialogueVisible = true;
	
	// ���������¼�������,����رնԻ���
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			dialogueBackground->setVisible(false);  // ���ضԻ���
			label->setVisible(false);  // ��������
			npcTalkImage->setVisible(false); // ������������
			nameLabel->setVisible(false);
			isDialogueVisible = false;
		}
		};
	// �������¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::initMouseListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (isDialogueVisible == false)
				Player::getInstance()->useCurrentTool();
		}
		};

	for (auto npc : npcs) {
		// ��������� NPC �ľ���
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());

		// �趨һ�����ʵľ�����ֵ
		float interactionRange = 100.0f;  // �ɵ�������ֵ����ʾ����� NPC ֮�����󽻻�����
		CCLOG("distance:(%f)\n", distance);
		// �������� NPC �ľ���С����ֵ���򴥷��Ի���
		if (distance < interactionRange) {
			listener->onMouseDown = [=](Event* event) {
				// ����Ƿ����Ҽ����
				if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT
					&& player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition()) < interactionRange) {
					showDialogue(npc);  // ��ʾ�Ի���
				}
				};
		}
	}
	// �������¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

