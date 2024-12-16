#include "Bag.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include "../Item/ItemFactory.h"

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

	// ��ʼ��������С
	items.resize(row * capacity, nullptr);
	quantities.resize(row * capacity, 0);
	itemLabels.resize(row * capacity, nullptr);

	// �������½ǵ�λ��
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // ������ʾ����Ļ�ײ�����ײ� 60 ����

	// ��������
	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0, "bagBackground");
	}

	// ���һЩ��Ʒ
	const std::vector<std::string> initItems = INIT_ITEMS;
	for (auto itemName : initItems) {
		auto item = ItemFactory::createItem(itemName);
		if (item) {
			addItem(item);
		}
	}

	// Ĭ�ϵ�ǰѡ�е�һ����Ʒ
	setSelectedItem(0);

	// ��ɫ�����ο�������ʾ��ǰ����Ʒ
	auto drawNode = DrawNode::create();
	const float expand = 4.0f;
	Vec2 bottomLeft(-expand, -expand * 1.5f);											// ���½Ƕ���
	Vec2 bottomRight = bottomLeft + Vec2(iconSize + 2 * expand, 0.0f);					// ���½Ƕ���
	Vec2 topRight = bottomLeft + Vec2(iconSize + 2 * expand, iconSize + 2 * expand);	// ���ϽǶ���
	Vec2 topLeft = bottomLeft + Vec2(0.0f, iconSize + 2 * expand);						// ���ϽǶ���
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
			addChild(item);
			quantities[i] = 1;

			// ������ǩ�����뱳��
			auto label = Label::createWithTTF(std::to_string(quantities[i]), ResPath::FONT_TTF, 14);
			itemLabels[i] = label;
			addChild(label, 3);
			updateDisplay();
			return true;
		}
	}
	return false;
}

// �ӱ������Ƴ���Ʒitem
void Bag::removeItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		// �Ƴ���ǰ����
		removeChild(items[index]);
		removeChild(itemLabels[index]);
		items[index] = nullptr;
		quantities[index] = 0;
		// �����ÿһ����Ʒ��ǰ��
		for (int i = index + 1; i < row * capacity - 1; ++i) {
			if (!items[i]) {
				break;
			}
			items[i - 1] = items[i];
			quantities[i - 1] = quantities[i];
			itemLabels[i - 1] = itemLabels[i];
		}
		updateDisplay();
	}
}

Item* Bag::getItem(const int index) const {
	if (index >= 0 && index < row * capacity) {
		return items[index];
	}
	return nullptr;
}

void Bag::setSelectedItem(const int index) {
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

		icon->setVisible(true);
		icon->setPosition(iconPositon);

		// ��ȡ��ǩ����ʾ��ǩ
		auto label = itemLabels[i];
		if (label && quantities[i] > 1) {
			label->setString(std::to_string(quantities[i])); // ����������ʾ
			const float dPosition = 4.0f;
			label->setPosition(icon->getPosition() + Vec2(iconSize / 2 - dPosition, -iconSize / 2 + dPosition));  // ��ʾ��ͼ������½�
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
int Bag::getItemIndex(const std::string& itemName) {
	// �����洢���ߵ�λ��
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == itemName) {
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

const Size& Bag::getContentSize() const {
	// ������ͼ���С���Ǳ��������Ĵ�С
	auto bagBackground = getChildByName("bagBackground");
	return bagBackground->getContentSize();
}

// �������
void Bag::clearBag() {
	for (int i = 0; i < row * capacity; ++i) {
		if (items[i]) {
			removeChild(items[i]);
			items[i] = nullptr;
			quantities[i] = 0;
		}
		if (itemLabels[i]) {
			removeChild(itemLabels[i]);
			itemLabels[i] = nullptr;
		}
	}
	selectedIndex = -1;
	updateDisplay();
}

// ������Ʒ
void Bag::setItem(const int index, Item* item, const int quantity) {
	if (index >= 0 && index < row * capacity) {
		// �Ƴ�������Ʒ
		if (items[index]) {
			removeChild(items[index]);
		}
		if (itemLabels[index]) {
			removeChild(itemLabels[index]);
		}
		// ��������Ʒ������
		items[index] = item;
		quantities[index] = quantity;
		addChild(item);

		// ������ǩ
		auto label = Label::createWithTTF(std::to_string(quantity), ResPath::FONT_TTF, 14);
		itemLabels[index] = label;
		addChild(label, 3);
		updateDisplay();
	}
}

// ��ȡ������
int Bag::getTotalCapacity() const { 
	return row * capacity; 
}

// ��ȡ������Ʒ������
const std::vector<Item*>& Bag::getItems() const { 
	return items; 
}

// ��ȡ������Ʒ������
const std::vector<int>& Bag::getQuantities() const { 
	return quantities; 
}
