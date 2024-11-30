#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Axe.h"

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
	
	// ������ʾ���ڵı�ǩ
	dateLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	if (dateLabel) {
		dateLabel->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 40));  // ���Ͻ�λ��
		this->addChild(dateLabel, 5);
	}

	// ����һ����ʱ����ÿ�����һ�� updateDate ����
	schedule([this](float deltaTime) {
		updateDate();
		}, 1.0f, "update_date_key");

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

	farmMap->npcInit(Vec2(origin.x + WIZARD_X, origin.y + WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(origin.x + CLEANER_X, origin.y + CLEANER_Y), cleaner);
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

	auto bag = Bag::create();
	this->addChild(bag, 4);
	auto pickaxe = Pickaxe::create();
	bag->addTool(pickaxe);
	auto axe = Axe::create();
	bag->addTool(axe);
	bag->selectTool(0);
	
	createFestivals();

	// ��ʼ�����̼�����
	initKeyboardListener();

	// ��ʼ����������
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

// ��ʾ��ʼ�Ի���
void Farm::showInitialDialogue(Npc* npc) {
	// ��ǶԻ�������ʾ
	isDialogueVisible = true;

	// ��ȡ��Ļ�ߴ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �����Ի��򱳾�
	auto dialogueBackground = Sprite::create("npcImages/dialogueBox.png");
	if (!dialogueBackground) {
		return;
	}

	// ��������ʾNPC�ĶԻ�����
	auto label = Label::createWithTTF(npc->printDialogue(), "fonts/Marker Felt.ttf", 44);
	dialogueBackground->setContentSize(Size(TALKING_BOX_WIDTH, TALKING_BOX_HEIGHT)); // ���öԻ����С
	dialogueBackground->setPosition(Vec2(TALKING_BOX_X, TALKING_BOX_Y));  // ���öԻ���λ��
	this->addChild(dialogueBackground, 10);

	// �������ֿ�
	label->setDimensions(LABEL_WIDTH, LABEL_HEIGHT);
	label->setPosition(Vec2(dialogueBackground->getPositionX() - 240, dialogueBackground->getPositionY()));
	label->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
	label->setTextColor(Color4B::WHITE);
	this->addChild(label, 11);

	// NPC����
	std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png";
	auto npcTalkImage = Sprite::create(npcImageName);
	if (npcTalkImage) {
		npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));
		this->addChild(npcTalkImage, 12);
	}

	// NPC����
	auto nameLabel = Label::createWithTTF(npc->getNpcName(), "fonts/Marker Felt.ttf", 40);
	nameLabel->setPosition(Vec2(dialogueBackground->getPositionX() + 360, dialogueBackground->getPositionY() - 140));
	nameLabel->setTextColor(Color4B::WHITE);
	this->addChild(nameLabel, 11);

	// ��������¼�������
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDialogueVisible) {
			// ��ʾѡ�ť
			showDialogueOptions(npc, dialogueBackground, label, npcTalkImage, nameLabel, listener);
		}
		};
	// �������¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::showDialogueOptions(Npc* npc, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, EventListenerMouse* lastListener) {
	_eventDispatcher->removeEventListener(lastListener);
	// ���ԭʼ�ĶԻ��ı�
	label->setVisible(false);

	// ѡ���ı�����
	std::vector<std::string> options = { "Relationship between us", "Any tasks?", "Community Celebrations", "I have a gift for you" };
	const float optionY = dialogueBackground->getPositionY() + 120;  // ѡ����ʾλ��

	// ����ѡ�ť
	for (int i = 0; i < options.size(); ++i) {
		auto optionButton = ui::Button::create();  // ������ť
		optionButton->setTitleText(options[i]);
		optionButton->setTitleFontSize(30);
		optionButton->setTitleColor(Color3B::WHITE);  // ����������ɫΪ��ɫ
		optionButton->setPosition(Vec2(dialogueBackground->getPositionX() - 240, optionY - (i * 60)));  // ���ð�ťλ��

		// Ϊÿ����ť��ӵ���¼�
		optionButton->addClickEventListener([=](Ref* sender) {
			updateDialogueAfterOptionSelected(npc, optionButtons, i, dialogueBackground, label, npcTalkImage, nameLabel);
			});

		optionButtons.push_back(optionButton);
		this->addChild(optionButton, 15);  // ����ť��ӵ�������
	}
}

void Farm::updateDialogueAfterOptionSelected(Npc* npc, std::vector<ui::Button*> optionButtons, int optionIndex, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel) {
	// ��������ѡ�ť
	for (auto button : optionButtons) {
		button->setTitleText("");
		button->setVisible(false);
	}
	std::string newDialogue;

	// ����ѡ���ѡ����¶Ի�������
	switch (optionIndex) {
		case 0:
			newDialogue = npc->printStatus();
			break;
		case 1:
			newDialogue = "Not yet";
			break;
		case 2:
			newDialogue = "The next festival will be a great celebration. You should join us!";
			break;
		case 3:
			newDialogue = "Oh, a gift? That's so kind of you. What did you bring me?";
			npc->interactWithPlayer();
			break;
		default:
			break;
	}

	label->setString(newDialogue);
	label->setVisible(true);  // ��ʾ�µĶԻ�����

	// ���´�������¼�������
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			closeDialogue(dialogueBackground, label, npcTalkImage, nameLabel, listener);
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::closeDialogue(Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, EventListenerMouse* lastListener) {
	_eventDispatcher->removeEventListener(lastListener);
	dialogueBackground->setVisible(false);
	label->setVisible(false);
	npcTalkImage->setVisible(false);
	nameLabel->setVisible(false);
	isDialogueVisible = false;
}

void Farm::initMouseListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (isDialogueVisible == false) {
				Player::getInstance()->useCurrentTool();
			}
		}
		else if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : npcs) {
				// ���������NPC�ľ���
				Player* player = Player::getInstance();
				FarmMap* farmMap = FarmMap::getInstance();
				const float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());
				// �趨һ�����ʵľ�����ֵ
				const float interactionRange = 100.0f;  // �ɵ�������ֵ����ʾ����� NPC ֮�����󽻻�����
				CCLOG("distance:(%f)\n", distance);
				if (distance < interactionRange && isDialogueVisible == false) {
					showInitialDialogue(npc);
				}
			}
		}
		};
	
	// �������¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ������������¼�
void Farm::createFestivals() {
	Festival* springFestival = Festival::create("Spring Festival", "Celebrate the arrival of Spring with games, food, and fun!", "Spring 13", true);
	if (springFestival) {
		festivals.push_back(springFestival);
	}

	Festival* summerFestival = Festival::create("Summer Festival", "The hot days of Summer are here! Time for the beach!", "Summer 11", false);
	if (summerFestival) {
		festivals.push_back(summerFestival);
	}
}

// ����Ƿ��ǽ��գ����������ջ
void Farm::checkFestivalEvent() {
	auto dateManager = DateManage::getInstance();
	std::string currentDate = dateManager->getCurrentDate();

	for (auto& festival : festivals) {
		if (festival->getEventDate() == currentDate) {
			// ��ǰ�������������ƥ�䣬��ʼ���ջ
			festival->startEvent(dateManager);
			break;
		}
	}
}

void Farm::updateDate() {
	// ��ȡ DateManage ʵ��
	DateManage* dateManager = DateManage::getInstance();

	// ����һ��
	dateManager->advanceDay();

	// ��ȡ��ǰ����ݡ����ں�����
	int year = dateManager->getCurrentYear();
	std::string season = dateManager->getCurrentSeason();
	int day = dateManager->getCurrentDay();

	// ���������ַ���
	std::stringstream dateStream;
	dateStream << season << " " << day << " - Year " << year;

	// ���� Label
	dateLabel->setString(dateStream.str());

	checkFestivalEvent();
}