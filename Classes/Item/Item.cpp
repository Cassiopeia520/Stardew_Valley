#include "Item.h"

Item::Item(const std::string& itemName, const std::string& itemImagePath, int itemQuantity)
    : name(itemName), imagePath(itemImagePath), quantity(itemQuantity) {
    // ʹ��ͼƬ·����������
    if (!this->initWithFile(imagePath)) {
        CCLOG("Failed to load image: %s", imagePath.c_str());
    }

    // ��ʼ��������ʾ������ʹ��һ�� Label ����ʾ������
    this->updateQuantityDisplay();
}

void Item::addQuantity(int count) {
    quantity += count;
    updateQuantityDisplay();  // ����������ʾ
}

void Item::updateQuantityDisplay() {
    // ��ʾ��Ʒ�������������������1����ʾ
    if (quantity > 1) {
        auto quantityLabel = cocos2d::Label::createWithTTF(std::to_string(quantity), "fonts/arial.ttf", 20);
        quantityLabel->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // �����ھ�����·�
        this->addChild(quantityLabel, 1);  // ��������ǩ��ӵ���Ʒ������
    }
}

// �������캯��
Item::Item(const Item& other)
    : name(other.name), imagePath(other.imagePath) {
}

// ��ֵ������
Item& Item::operator=(const Item& other) {
    if (this != &other) {
        name = other.name;
        imagePath = other.imagePath;
    }
    return *this;
}

void Item::increaseCount() {
    quantity++;
}
bool Item::isSameItem(const Item& other) const {
    return name == other.name;
}