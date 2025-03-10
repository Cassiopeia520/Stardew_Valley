/****************************************************************
 * File Function: 实现背包类
 * Author:        赵卓冰 韦瑾钰
 ****************************************************************/
#include "Bag.h"
#include "../Player/Player.h"
#include "../Tool/Seed.h"
#include "../Tool/Fertilizer.h"
#include "../Tool/MilkingPail.h"
#include "../Tool/Agrochemical.h"
#include "../Animal/AnimalItem.h"
#include "../Constant/Constant.h"
#include "../Item/ItemFactory.h"

USING_NS_CC;

// 初始化静态成员变量
Bag* Bag::instance = nullptr;

// 获取背包实例
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

// 背包析构函数
Bag::~Bag() {
	if (instance != nullptr) {
		instance = nullptr;
	}
}

// 初始化
bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// 初始化背包大小
	items.resize(row * capacity, nullptr);
	quantities.resize(row * capacity, 0);
	itemLabels.resize(row * capacity, nullptr);

	// 背包左下角的位置
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // 背包显示在屏幕底部，距底部 60 像素

	// 背包背景
	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		addChild(bagBackground, 0, "bagBackground");
	}

	// 添加一些物品
	const std::vector<std::string> initItems = INIT_ITEMS;
	for (auto itemName : initItems) {
		auto item = ItemFactory::createItem(itemName);
		if (item) {
			addItem(item);
		}
	}

	// 默认当前选中第一个物品
	setSelectedItem(0);

	// 红色正方形框，用于显示当前的物品
	auto drawNode = DrawNode::create();
	const float expand = 4.0f;
	Vec2 bottomLeft(-expand, -expand * 1.5f);											// 左下角顶点
	Vec2 bottomRight = bottomLeft + Vec2(iconSize + 2 * expand, 0.0f);					// 右下角定点
	Vec2 topRight = bottomLeft + Vec2(iconSize + 2 * expand, iconSize + 2 * expand);	// 右上角顶点
	Vec2 topLeft = bottomLeft + Vec2(0.0f, iconSize + 2 * expand);						// 左上角顶点
	Vec2 vertices[] = { bottomLeft, bottomRight, topRight, topLeft };
	drawNode->drawPolygon(
		vertices,               // 顶点数组
		4,                      // 顶点个数
		Color4F(0, 0, 0, 0),    // 填充颜色（透明）
		2.0f,                   // 边框宽度
		Color4F::RED            // 边框颜色（红色）
	);
	addChild(drawNode, 2, "drawNode");

	// 更新显示
	updateDisplay();
	return true;
}

// 向背包增加物品
bool Bag::addItem(Item* item) {
	// 遍历整个背包
	for (int i = 0; i < row * capacity; ++i) {
		// 要加入的物品已经在背包中存在
		if (items[i] && (item->getItemName() == items[i]->getItemName())) {
			quantities[i]++;
			updateDisplay();
			return true;
		}
		// 找到了一个空位
		if (items[i] == nullptr) {
			items[i] = item;
			addChild(item);
			quantities[i] = 1;

			// 创建标签并加入背包
			auto label = Label::createWithTTF(std::to_string(quantities[i]), ResPath::FONT_TTF, 14);
			itemLabels[i] = label;
			addChild(label, 3);
			updateDisplay();
			return true;
		}
	}
	return false;
}

// 从背包中移出物品item
Item* Bag::removeItem(const int index) {
	// 不允许删除工具
	if (index >= 4 && index < row * capacity && items[index]) {
		Item* item = items[index];
		int size = getSize() - 1;
		if (quantities[index] == 1) {
			removeChild(items[index]);
			// 后面的每一个物品向前移
			int i = index + 1;
			for (; i < getSize(); ++i) {
				if (!items[i] || i == row * capacity) {
					break;
				}
				items[i - 1] = items[i];
				quantities[i - 1] = quantities[i];
				itemLabels[i - 1] = itemLabels[i];
			}
			// 保证最后一个物品正确更新
			items[i - 1] = nullptr;
			quantities[i - 1] = 0;
			itemLabels[i - 1] = nullptr;
			updateDisplay();
			//防止删除末端物品使用出错
			if (index == size) {
				setSelectedItem(index - 1);
			}
			else {
				setSelectedItem(index);
			}
		}
		else {
			quantities[index]--;
			updateDisplay();
		}
		
		return item;
	}
	return nullptr;
}

// 从背包获取物品的序号
Item* Bag::getItem(const int index) const {
	if (index >= 0 && index < row * capacity) {
		return items[index];
	}
	return nullptr;
}

// 选中对应序号的物品
void Bag::setSelectedItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		selectedIndex = index;
		Player::getInstance()->setCurrentItem(items[index]);
	}
	updateDisplay();
}

// 获取选中物品的序号
Item* Bag::getSelectedItem() const {
	if (selectedIndex >= 0 && selectedIndex < row * capacity && items[selectedIndex]) {
		return items[selectedIndex];
	}
	return nullptr;
}

// 更新背包的显示
void Bag::updateDisplay() {
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 2) * spacing) / 2;
	const float startY = 100.0f; // 背包显示在屏幕底部，距底部 100 像素

	// 更新工具图标
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

		// 获取标签并显示标签
		auto label = itemLabels[i];
		if (label && quantities[i] > 1) {
			label->setString(std::to_string(quantities[i])); // 设置数量显示
			const float dPosition = 4.0f;
			label->setPosition(icon->getPosition() + Vec2(iconSize / 2 - dPosition, -iconSize / 2 + dPosition));  // 显示在图标的右下角
		}
		else
			label->setString("");

		// 红色矩形框
		if (i == selectedIndex) {
			auto drawNode = getChildByName("drawNode");
			if (drawNode) {
				drawNode->setPosition(iconPositon - Vec2(iconSize / 2, iconSize / 2));
			}
		}

		// 如果是选中物品,添加高亮
		if (i == selectedIndex) {
			icon->setColor(Color3B::ORANGE);
		}
		else {
			icon->setColor(Color3B::WHITE);
		}
	}
}

// 获取工具的索引
int Bag::getItemIndex(const std::string& itemName) {
	// 遍历存储工具的位置
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == itemName) {
			return i;
		}
	}
	return 0; // 没找到就默认第一个
}

int Bag::getSize() {
	for (int i = 0; i < row * capacity; ++i) {
		if (items[i] == nullptr) {
			return i;
		}
	}
	return row * capacity;
}

// 获取背包大小
const Size& Bag::getContentSize() const {
	// 背包的图像大小就是背包背景的大小
	auto bagBackground = getChildByName("bagBackground");
	return bagBackground->getContentSize();
}

// 清除背包
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

// 设置物品
void Bag::setItem(const int index, Item* item, const int quantity) {
	if (index >= 0 && index < row * capacity) {
		// 移除现有物品
		if (items[index]) {
			removeChild(items[index]);
		}
		if (itemLabels[index]) {
			removeChild(itemLabels[index]);
		}
		// 设置新物品和数量
		items[index] = item;
		quantities[index] = quantity;
		addChild(item);

		// 创建标签
		auto label = Label::createWithTTF(std::to_string(quantity), ResPath::FONT_TTF, 14);
		itemLabels[index] = label;
		addChild(label, 3);
		updateDisplay();
	}
}

// 获取总容量
int Bag::getTotalCapacity() const { 
	return row * capacity; 
}

// 获取所有物品的向量
const std::vector<Item*>& Bag::getItems() const { 
	return items; 
}

// 获取所有物品的数量
const std::vector<int>& Bag::getQuantities() const { 
	return quantities; 
}

// 查看背包中是否有目标物品
bool Bag::checkItemIn(const std::string& targetName) {
	for (auto item : items) {
		if (item) {
			if (item->getItemName() == targetName) {
				return true;
			}
		}
	}
	return false;
}
