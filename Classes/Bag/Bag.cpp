#include "Bag.h"
#include "../Tool/Axe.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/Kettle.h"
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
	items.resize(row * capacity, nullptr);
	quantities.resize(row * capacity, 0);
	selectedIndex = 0;

	// ���������½�λ��
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // ������ʾ����Ļ�ײ�����ײ� 60 ����

	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}

	// ��ʼ������ͼ��
	for (int i = 0; i < row * capacity; ++i) {
		auto label = Label::createWithTTF(std::to_string(quantities[i]), ResPath::FONT_TTF, 30);
		label->setVisible(false);
		itemLabels.push_back(label);
		addChild(label, 2);
	}

	// ��ӳ�ʼ������Ʒ
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

	// ����һ�� DrawNode ����
	auto drawNode = DrawNode::create();

	// ���������ε��ĸ�����
	Vec2 bottomLeft(0,0);									// ���½Ƕ���
	Vec2 bottomRight = bottomLeft + Vec2(iconSize, 0.0f);	// ���½Ƕ���
	Vec2 topRight = bottomLeft + Vec2(iconSize, iconSize);	// ���ϽǶ���
	Vec2 topLeft = bottomLeft + Vec2(0.0f, iconSize);		// ���ϽǶ���

	// ʹ�� drawPolygon ���ƺ�ɫ�߿��������
	Vec2 vertices[] = { bottomLeft, bottomRight, topRight, topLeft };
	drawNode->drawPolygon(
		vertices,               // ��������
		4,                      // �������
		Color4F(0, 0, 0, 0),    // �����ɫ��͸����
		2.0f,                   // �߿���
		Color4F::RED            // �߿���ɫ����ɫ��
	);
	addChild(drawNode, 2, "drawNode");

	// ������ʾ
	updateDisplay();
	return true;
}

bool Bag::addItem(Item* item) {
	// ������������
	for (int i = 0; i < row * capacity; ++i) {
		// Ҫ�������Ʒ�Ѿ��ڱ����д���
		if (items[i] && (item->getItemName() == items[i]->getItemName())) {
			quantities[i]++;
			updateDisplay();
			return true;
		}
		// �ҵ���һ����λ
		if (items[i] == nullptr) {
			items[i] = item;
			quantities[i] = item->getQuantity();
			addChild(item);
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		removeChild(items[index]);
		items[index] = nullptr;
		updateDisplay();
	}
}

Item* Bag::getItem(const int index) const {
	if (index >= 0 && index < row * capacity) {
		return items[index];
	}
	return nullptr;
}

void Bag::selectItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
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
	const auto WINSIZE = Director::getInstance()->getVisibleSize();
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 2) * spacing) / 2;
	const float startY = 100.0f; // ������ʾ����Ļ�ײ�����ײ� 100 ����

	// ���¹���ͼ��
	for (int i = 0; i < row * capacity; ++i) {
		auto icon = items[i];
		if (icon == nullptr) {
			continue;
		}
		const auto iconPositon = Vec2(
			startX + i % capacity * (iconSize + spacing) + iconSize / 2,
			startY + iconSize / 2 - (iconSize + spacing) * (i / capacity));

		auto label = itemLabels[i];
		icon->setVisible(true);
	
		// ����λ��
		icon->setPosition(iconPositon);
		if (label) {
			label->setPosition(icon->getPosition() + Vec2(20, 20));  // ��ʾ��ͼ������Ͻ�
			// ��������һ��
			if (quantities[i] > 1) {
				label->setString(std::to_string(quantities[i])); // ����������ʾ
			}
		}

		// ��ɫ���ο�
		if (i == selectedIndex) {
			auto drawNode = getChildByName("drawNode");
			if (drawNode) {
				drawNode->setPosition(iconPositon - Vec2(iconSize / 2, iconSize / 2));
			}
		}

		// �����ѡ����Ʒ,��Ӹ���
		if (i == selectedIndex) {
			icon->setColor(Color3B::ORANGE);
		}
		else {
			icon->setColor(Color3B::WHITE);
		}
	}
}

// ��ȡ���ߵ�����
int Bag::getToolIndex(const std::string& toolName) {
	// �����洢���ߵ�λ��
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == toolName) {
			return i;
		}
	}
	return 0; // û�ҵ���Ĭ�ϵ�һ��
}

int Bag::getSize() {
	for (int i = 0; i < row * capacity; ++i) {
		if (items[i] == nullptr) {
			return i;
		}
	}
	return row * capacity;
}