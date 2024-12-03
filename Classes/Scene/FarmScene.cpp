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

	// ������ʾ���ڵı�ǩ
	dateLabel = Label::createWithTTF("", ResPath::FONT_TTF, 24);
	if (dateLabel) {
		dateLabel->setPosition(Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // ���Ͻ�λ��
		this->addChild(dateLabel, 5);
	}

	// ??��ʱ��
	// ����һ����ʱ����ÿ�����һ�� updateDate ����
	schedule([this](float deltaTime) {
		updateDate();
		}, 1.0f, "update_date_key");

	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmMap.tmx")) {
		return false;
	}

	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(WINSIZE.width / 2 -farmMapSize.width / 2, WINSIZE.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// ���� NPC ʾ��
	Npc* wizard = new Npc(WIZARD);
	Npc* cleaner = new Npc(CLEANER);
	cleaner->increaseFriendship(90); // ���ܶ�90
	npcs.push_back(cleaner);
	npcs.push_back(wizard);
	farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	isDialogueVisible = false;

	// ���
	auto player = Player::getInstance();
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // ��ҳ�ʼλ������Ļ����
	this->addChild(player, 3);

	// �������
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		this->addChild(nameLabel, 4);
	}

	// ����
	Bag* bag = Bag::getInstance();
	this->addChild(bag, 4);

	createFestivals();

	// ��ʼ�����̼�����
	initKeyboardListener();

	// ��ʼ����������
	initMouseListener();

	return true;
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
		this->addChild(npcTalkImage, 11);
	}

	// NPC����
	auto nameLabel = Label::createWithTTF(npc->getNpcName(), ResPath::FONT_TTF, 40);
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
		this->addChild(optionButton, 12);  // ����ť��ӵ�������
	}
}

void Farm::updateDialogueAfterOptionSelected(Npc* npc, std::vector<ui::Button*> optionButtons, int optionIndex, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel) {
	// ��������ѡ�ť
	for (auto button : optionButtons) {
		button->setTitleText("");
		button->setVisible(false);
	}
	std::string newDialogue;
	DateManage* dateManage = DateManage::getInstance();
	// ����ѡ���ѡ����¶Ի�������
	switch (optionIndex) {
		case 0:
			newDialogue = npc->printStatus();
			break;
		case 1:
			newDialogue = "Not yet";
			break;
		case 2:
			newDialogue = dateManage->getNextFestival();
			break;
		case 3:
			//ѡ���������gift
			newDialogue = npc->giveGift("Milk");
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

void Farm::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
			const int index = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1);
			Bag::getInstance()->selectTool(index);
		}
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

void Farm::initMouseListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (isDialogueVisible == false) {
				Player::getInstance()->useCurrentTool();
				Vec2 playerPosition = player->getPosition();
				farmMap->interactWithFarmMap();
			}
		}
		else if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : npcs) {
				// ���������NPC�ľ���
				Player* player = Player::getInstance();
				FarmMap* farmMap = FarmMap::getInstance();
				const float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());
				// �趨һ�����ʵľ�����ֵ
				const float interactionRange = 100.0f;  // �ɵ�������ֵ����ʾ����� NPC ֮�����󽻻�����
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
	FarmMap* farmMap = FarmMap::getInstance();
	Festival* springFestival = Festival::create("Spring Festival", "Celebrate the arrival of Spring with games, food, and fun!", "Spring 7", true);
	if (springFestival) {
		farmMap->festivals.push_back(springFestival);
	}

	Festival* summerFestival = Festival::create("Summer Festival", "The hot days of Summer are here! Time for the beach!", "Summer 15", false);
	if (summerFestival) {
		farmMap->festivals.push_back(summerFestival);
	}

	Festival* fallFestival = Festival::create("Fall Festival", "Let's picking up the falling leaves!", "Fall 5", false);
	if (fallFestival) {
		farmMap->festivals.push_back(fallFestival);
	}

	Festival* winterFestival = Festival::create("Winter Festival", "Merry Christmas and Happy Birthday to levi!", "Winter 25", false);
	if (winterFestival) {
		farmMap->festivals.push_back(winterFestival);
	}
}

// ����Ƿ��ǽ��գ����������ջ
void Farm::checkFestivalEvent() {
	auto dateManager = DateManage::getInstance();
	std::string currentDate = dateManager->getCurrentDate();
	FarmMap* farmMap = FarmMap::getInstance();
	for (auto& festival : farmMap->festivals) {
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
