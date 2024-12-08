#include "Bag.h"
#include "../Tool/Axe.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/WateringCan.h"
#include "../Player/Player.h"
#include "../Tool/Seed.h"
#include "../Tool/Fertilizer.h"
#include "../Constant/Constant.h"

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

Bag::Bag() {}

Bag::~Bag() {
	if (instance != nullptr) {
		instance = nullptr;
	}
}

bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// ��ʼ������
	items.resize(capacity, nullptr);
	selectedIndex = 0;

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50.0f; // ������ʾ����Ļ�ײ�����ײ� 50 ����


	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}


	// ��ʼ������ͼ��
	for (int i = 0; i < capacity; ++i) {
		auto icon = Sprite::create(); // �հ�ͼ��
		icon->setVisible(false);
		addChild(icon);
		itemIcons.push_back(icon);
	}

	// ������ʾ
	updateDisplay();

	Tool* axe = Axe::create();
	addItem(axe);
	Tool* pickaxe = Pickaxe::create();
	addItem(pickaxe);
	Tool* hoe = Hoe::create();
	addItem(hoe);
	Tool* fisingRod = FishingRod::create();
	addItem(fisingRod);
	Tool* scythe = Scythe::create();
	addItem(scythe);
	Tool* kettle = Kettle::create();
	addItem(kettle);
	Tool* appleSeed = AppleSeed::create();
	addItem(appleSeed);
	Tool* cornSeed = CornSeed::create();
	addItem(cornSeed);
	Tool* carrotSeed = CarrotSeed::create();
	addItem(carrotSeed);
	Tool* fertilizer = Fertilizer::create();
	addItem(fertilizer);
	selectItem(0);

	return true;
}

bool Bag::addItem(Item* item) {
	// ����Ƿ��п�λ
	for (int i = 0; i < capacity; ++i) {
		if (items[i] == nullptr) {
			items[i] = item;
			addChild(item);
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeItem(const int index) {
	if (index >= 0 && index < capacity && items[index]) {
		removeChild(items[index]);
		items[index] = nullptr;
		updateDisplay();
	}
}

Item* Bag::getItem(const int index) const {
	if (index >= 0 && index < capacity) {
		return items[index];
	}
	return nullptr;
}

void Bag::selectItem(const int index) {
	if (index >= 0 && index < capacity && items[index]) {
		selectedIndex = index;
		Player::getInstance()->setCurrentItem(items[index]);
	}
	updateDisplay();
}

Item* Bag::getSelectedItem() const {
	if (selectedIndex >= 0 && selectedIndex < capacity && items[selectedIndex]) {
		return items[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50.0f; // ������ʾ����Ļ�ײ�����ײ� 50 ����

	// ���¹���ͼ��
	for (int i = 0; i < capacity; ++i) {
		auto icon = itemIcons[i];
		if (items[i]) {
			icon->setTexture("tools/" + items[i]->getItemName() + ".png");
			icon->setVisible(true);
		}
		else
			icon->setVisible(false);

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

// ��ȡ���ߵ�����
int Bag::getToolIndex(std::string toolName) {
	// �����洢���ߵ�λ��
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == toolName) {
			return i;
		}
	}
}