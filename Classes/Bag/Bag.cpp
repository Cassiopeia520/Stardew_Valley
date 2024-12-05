#include "Bag.h"
#include "../Tool/Axe.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/WateringCan.h"
#include "../Player/Player.h"
#include "../Tool/Seed.h"

USING_NS_CC;

// ��ʼ����̬��Ա����
Bag* Bag::instance = nullptr;

Bag* Bag::getInstance() {
	if (instance == nullptr) {
		instance = new (std::nothrow) Bag();
		if (instance && instance->init()) {
			instance->autorelease();
		}
		else {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

Bag::Bag(): selectedIndex(0) {}
Bag::~Bag() {}

bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// ��ʼ������
	tools.resize(capacity, nullptr);
	selectedIndex = 0;

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50.0f; // ������ʾ����Ļ�ײ�����ײ� 50 ����


	bagBackground = Sprite::create("icon/bagBackground.png");
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}


	// ��ʼ������ͼ��
	for (int i = 0; i < capacity; ++i) {
		auto icon = Sprite::create(); // �հ�ͼ��
		icon->setVisible(false);
		addChild(icon);
		toolIcons.push_back(icon);
	}

	// ������ʾ
	updateDisplay();

	Tool* axe = Axe::create();
	addTool(axe);
	Tool* pickaxe = Pickaxe::create();
	addTool(pickaxe);
	Tool* hoe = Hoe::create();
	addTool(hoe);
	Tool* fisingRod = FishingRod::create();
	addTool(fisingRod);
	Tool* scythe = Scythe::create();
	addTool(scythe);
	Tool* kettle = Kettle::create();
	addTool(kettle);
	Tool* seed = Seed::create();
	addTool(seed);
	selectTool(0);

	return true;
}

bool Bag::addTool(Tool* tool) {
	// ����Ƿ��п�λ
	for (int i = 0; i < capacity; ++i) {
		if (tools[i] == nullptr) {
			tools[i] = tool;
			addChild(tool);
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeTool(int index) {
	if (index >= 0 && index < capacity && tools[index]) {
		removeChild(tools[index]);
		tools[index] = nullptr;
		updateDisplay();
	}
}

Tool* Bag::getTool(int index) const {
	if (index >= 0 && index < capacity) {
		return tools[index];
	}
	return nullptr;
}

void Bag::selectTool(int index) {
	if (index >= 0 && index < capacity && tools[index]) {
		selectedIndex = index;
		Player::getInstance()->setCurrentTool(tools[index]);
	}
	updateDisplay();
}

Tool* Bag::getSelectedTool() const {
	if (selectedIndex >= 0 && selectedIndex < capacity && tools[selectedIndex]) {
		return tools[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
 	const float startY = 50.0f; // ������ʾ����Ļ�ײ�����ײ� 50 ����

	// ���¹���ͼ��
	for (int i = 0; i < capacity; ++i) {
		auto icon = toolIcons[i];
		if (tools[i]) {
			icon->setTexture("tools/" + tools[i]->getToolName() + ".png");
			icon->setVisible(true);
		}
		else {
			icon->setVisible(false);
		}

		// ����λ��
		icon->setPosition(Vec2(
			startX + i * (iconSize + spacing) + iconSize / 2,
			startY + iconSize / 2
		));

		// �����ѡ�й���,��Ӹ���
		if (i == selectedIndex) {
			icon->setColor(Color3B::YELLOW);
		}
		else {
			icon->setColor(Color3B::WHITE);
		}
	}
}

// �������Ŀ���
void Bag::toggleToolBar(bool show) {

}