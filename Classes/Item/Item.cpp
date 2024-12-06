#include "Item.h"

// create���������ڴ��������س�ʼ����Item����
Item* Item::create(const FishInfo& fish_info) {
    Item* item = new Item();
    if (item && item->init(fish_info)) {
        return item;
    }
    delete item;  // ��ʼ��ʧ��ʱ��ɾ������
    return nullptr;
}

// init���������ڳ�ʼ��Item������ڲ�״̬
bool Item::init(const FishInfo& fish_info) {
    this->name = fish_info.name;
    this->imagePath = fish_info.image;
    this->quantity = fish_info.quantity;
    this->isEdible = fish_info.isEdible;

    // ʹ��ͼƬ·����������
    this->initWithFile(imagePath);

    // ��ʼ��������ʾ������ʹ��һ�� Label ����ʾ������
    this->updateQuantityDisplay();

    return true;  // ����true��ʾ��ʼ���ɹ�
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