#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"

USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	DateManage* dateManage = DateManage::getInstance();
	// ����һ����ʱ����ÿ�����һ�� updateDate ����
	schedule([this, dateManage](float deltaTime) {
		dateManage->updateDate();
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
	DialogueBox::isDialogueVisible = false;

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
	if (bag) {
		this->addChild(bag, 4);
	}

	// �˳���ť
	auto closeButton = MyButton::create(ResPath::CLOSE_BUTTON_NORMAL, ResPath::CLOSE_BUTTON_HOVER);
	if (closeButton) {
		const auto closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // �������Ͻ�
		this->addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	// ��ʼ�����̼�����
	// initKeyboardListener();

	Control* control = Control::create();
	this->addChild(control, 4);

	 // ��ʼ����������
	 initMouseListener();
	 // ������ʾ���ڵı�ǩ
	 if (dateManage->dateLabel) {
		 dateManage->dateLabel->setPosition(Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // ���Ͻ�λ��
		 this->addChild(dateManage->dateLabel, 5);
	 }
	return true;
}

void Farm::initMouseListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		player->stopMoving();
		farmMap->stopMoving();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (DialogueBox::isDialogueVisible == false) {
				player->useCurrentTool();
				farmMap->interactWithFarmMap();
			}
		}
		else if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : npcs) {
				// ���������NPC�ľ���
				const float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());
				// �趨һ�����ʵľ�����ֵ
				const float interactionRange = 100.0f;  // �ɵ�������ֵ����ʾ����� NPC ֮�����󽻻�����
				if (distance < interactionRange && DialogueBox::isDialogueVisible == false) {
					if (!DialogueBox::isDialogueVisible) {
						DialogueBox* dialogueBox = DialogueBox::create(npc);
						this->addChild(dialogueBox, 5);
						dialogueBox->showInitialDialogue();
						break;
					}
				}
			}
		}
		};
	
	// �������¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


// �رհ�ť�Ļص�����
void Farm::closeButtonClicked(Ref* pSender) {
	Director::getInstance()->popScene();
}

// �������
void Farm::animalManager() {

}