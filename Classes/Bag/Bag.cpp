#include "Bag.h"

USING_NS_CC;

Bag* Bag::create() {
	Bag* bag = new (std::nothrow) Bag();
	if (bag && bag->init()) {
		bag->autorelease();
		return bag;
	}
	CC_SAFE_DELETE(bag);
	return nullptr;
}

bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// ��ʼ������
	tools.resize(capacity, nullptr);
	selectedIndex = -1; // �޷�ѡ�й���

	// ��������������
	bagBackground = DrawNode::create();
	addChild(bagBackground);

	// ��ʼ������ͼ��
	for (int i = 0; i < capacity; ++i) {
		auto icon = Sprite::create(); // �հ�ͼ��
		icon->setVisible(false);
		addChild(icon);
		toolIcons.push_back(icon);
	}

	// ������ʾ
	updateDisplay();

	return true;
}

bool Bag::addTool(Tool* tool) {
	// ����Ƿ��п�λ
	for (int i = 0; i < capacity; ++i) {
		if (tools[i] == nullptr) {
			tools[i] = tool;
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeTool(int index) {
	if (index >= 0 && index < capacity) {
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
	if (index >= 0 && index < capacity && tools[index] != nullptr) {
		selectedIndex = index;
	}
	updateDisplay();
}

Tool* Bag::getSelectedTool() const {
	if (selectedIndex >= 0 && selectedIndex < capacity) {
		return tools[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50; // ������ʾ����Ļ�ײ�����ײ� 50 ����

	// ���Ʊ�����
	bagBackground->clear();
	bagBackground->drawSolidRect(
		Vec2(startX - 10, startY - 10),
		Vec2(startX + capacity * (iconSize + spacing) - spacing + 10, startY + iconSize + 10),
		Color4F(0, 0, 0, 0.5f) // ��͸����ɫ����
	);

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