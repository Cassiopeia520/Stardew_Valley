#include "Food.h"

// create���������ڴ��������س�ʼ����Food����
Food* Food::create(const ItemInfo& item_info) {
    Food* food = new Food();

    // ʹ�� item_info ��ʼ�� Food ��״̬
    if (food && food->init(item_info)) {

        // ��ʼ��������ʾ
        food->updateQuantityDisplay();

        return food;
    }

    delete food;  // ��ʼ��ʧ��ʱ��ɾ������
    return nullptr;
}


// init���������ڳ�ʼ��Food������ڲ�״̬
bool Food::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    quantity = item_info.quantity;
    return true;  // ����true��ʾ��ʼ���ɹ�
}

void Food::useItem()
{
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

//// �������캯��
//Food::Food(const Food& other)
//    : itemName(other.itemName), itemImage(other.itemImage) {
//}
//
//// ��ֵ������
//Food& Food::operator=(const Food& other) {
//    if (this != &other) {
//        name = other.name;
//        imagePath = other.imagePath;
//    }
//    return *this;
//}

void Food::increaseCount() {
    quantity++;
}

bool Food::isSameItem(const Food& other) const {
    return itemName == other.itemName;
}