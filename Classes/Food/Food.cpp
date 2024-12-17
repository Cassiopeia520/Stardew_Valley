#include "Food.h"

// create���������ڴ��������س�ʼ����Food����
Food* Food::create(const ItemInfo& item_info) {
    Food* food = new (std::nothrow) Food();

    // ʹ�� item_info ��ʼ�� Food ��״̬
    if (food && food->init(item_info)) {
        food->autorelease();
        return food;
    }
    else {
        CC_SAFE_DELETE(food);
        return nullptr;
    }
}

// init���������ڳ�ʼ��Food������ڲ�״̬
bool Food::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    return Sprite::initWithFile(item_info.image);
}

void Food::useItem()
{
}

bool Food::isSameItem(const Food& other) const {
    return itemName == other.itemName;
}