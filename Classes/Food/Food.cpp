#include "Food.h"

// create���������ڴ��������س�ʼ����Food����
Food* Food::create(const FishInfo& fish_info) {
    Food* food = new Food();
    if (food && food->init(fish_info)) {
        return food;
    }
    delete food;  // ��ʼ��ʧ��ʱ��ɾ������
    return nullptr;
}

// init���������ڳ�ʼ��Food������ڲ�״̬
bool Food::init(const FishInfo& fish_info) {
    name = fish_info.name;
    imagePath = fish_info.image;
    quantity = fish_info.quantity;

    // ʹ��ͼƬ·����������
    initWithFile(imagePath);

    // ��ʼ��������ʾ������ʹ��һ�� Label ����ʾ������
    updateQuantityDisplay();

    return true;  // ����true��ʾ��ʼ���ɹ�
}

void Food::addQuantity(int count) {
    quantity += count;
    updateQuantityDisplay();  // ����������ʾ
}

void Food::updateQuantityDisplay() {
    // ��ʾ��Ʒ�������������������1����ʾ
    if (quantity > 1) {
        auto quantityLabel = cocos2d::Label::createWithTTF(std::to_string(quantity), "fonts/arial.ttf", 20);
        quantityLabel->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // �����ھ�����·�
        addChild(quantityLabel, 1);  // ��������ǩ��ӵ���Ʒ������
    }
}

// �������캯��
Food::Food(const Food& other)
    : name(other.name), imagePath(other.imagePath) {
}

// ��ֵ������
Food& Food::operator=(const Food& other) {
    if (this != &other) {
        name = other.name;
        imagePath = other.imagePath;
    }
    return *this;
}

void Food::increaseCount() {
    quantity++;
}

bool Food::isSameItem(const Food& other) const {
    return name == other.name;
}