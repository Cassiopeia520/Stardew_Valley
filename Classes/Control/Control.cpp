#include "Control.h"
#include "../Constant/Constant.h"
#include "../Map/FarmMap.h"
#include "../Bag/Bag.h"
#include "../Player/Player.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Skill/SkillTreeUI.h"

USING_NS_CC;

std::set<cocos2d::EventKeyboard::KeyCode> Control::keysPressed;

Control* Control::create() {
	Control* control = new(std::nothrow) Control();
	if (control && control->init()) {
		control->autorelease();
		return control;
	}
	CC_SAFE_DELETE(control);
	return nullptr;
}

bool Control::init() {
	if (!Node::init()) {
		return false;
	}
	initKeyboardListener();
	initMouseListener();

	return true;
}

void Control::updateMovement() {
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

void Control::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();

	auto skillTreeLayer = SkillTreeUI::getInstance();
	addChild(skillTreeLayer);
	listener->onKeyPressed = [this, skillTreeLayer](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_E) {
			if (SkillTreeUI::isOpen == false) {
				skillTreeLayer->setVisible(true);
				skillTreeLayer->openSkill();
				SkillTreeUI::isOpen = true;
				Player::getInstance()->setUseItemEnable(false);
			}
			else {
				skillTreeLayer->setVisible(false);
				SkillTreeUI::isOpen = false;
				Player::getInstance()->setUseItemEnable(true);
			}
		}
		if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
			const int index = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1);
			Bag::getInstance()->selectItem(index);
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

void Control::initMouseListener()
{
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	listener->onMouseScroll = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		const int scrollY = static_cast<int>(mouseEvent->getScrollY()); // ��ֱ����ֵ
		auto bag = Bag::getInstance();
		int targetIndex = bag->getSelectedIndex() + scrollY;
		if (targetIndex < 0) {
			targetIndex = 0;
		}
		if (targetIndex > bag->getSize() - 1) {
			targetIndex = bag->getSize() - 1;
		}
		bag->selectItem(targetIndex);
		};

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (DialogueBox::isDialogueVisible == false) {
				player->stopMoving();
				farmMap->stopMoving();
				player->useCurrentItem();
				farmMap->interactWithFarmMap();
			}
		}
		else if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : Farm::npcs) {
				// ���������NPC�ľ���
				const float distance = player->getPosition().distance(npc->getPosition() + farmMap->getPosition());

				// ������С�ڽ������벢�Ҵ�ʱ�Ի���û����ʾ
				if (distance < INTERACTION_RANGE && DialogueBox::isDialogueVisible == false) {
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