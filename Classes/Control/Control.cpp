#include "Control.h"
#include "../Constant/Constant.h"
#include "../Map/FarmMap.h"
#include "../Bag/Bag.h"
#include "../Player/Player.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Skill/SkillTreeUI.h"

USING_NS_CC;

// ���캯��
Control::Control() : sceneMap(nullptr) {}

// ��������
Control::~Control() {}

// ��̬����Control����
Control* Control::create(SceneMap* sceneMap) {
	Control* control = new(std::nothrow) Control();
	if (control  && sceneMap && control->init(sceneMap)) {
		control->autorelease();
		return control;
	}
	CC_SAFE_DELETE(control);
	return nullptr;
}

// ��ʼ��
bool Control::init(SceneMap* sceneMap) {
	if (!Node::init()) {
		return false;
	}
	this->sceneMap = sceneMap;
	initKeyboardListener();
	initMouseListener();
	return true;
}

// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ���
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
	auto mapMoveDirection = -direction;
	if (sceneMap) {
		sceneMap->moveMapByDirection(mapMoveDirection);
	}
	if (player) {
		player->moveByDirection(direction);
	}
}

// ��ʼ�����̼�����
void Control::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();
	// ��ȡ������UI�����
	auto skillTreeLayer = SkillTreeUI::getInstance();
	addChild(skillTreeLayer);
	listener->onKeyPressed = [this, skillTreeLayer](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_E) {
			if (SkillTreeUI::isOpen == false) {
				skillTreeLayer->setVisible(true);
				skillTreeLayer->openSkillUI();
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
			Bag::getInstance()->setSelectedItem(index);
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

// ��ʼ����������
void Control::initMouseListener() {
	// ��������¼�������
	auto listener = EventListenerMouse::create();

	// ����������
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
		bag->setSelectedItem(targetIndex);
		};

	// ������갴��
	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (DialogueBox::isDialogueVisible == false) {
				player->stopMoving();
				sceneMap->stopMoving();
				player->useCurrentItem();
				sceneMap->interactWithMap();
			}
		}
		else if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : Farm::npcs) {
				// ���������NPC�ľ���
				const float distance = player->getPosition().distance(npc->getPosition() + sceneMap->getPosition());

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