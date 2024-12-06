#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h"
#include "../Constant/Constant.h"

class Item : public cocos2d::Sprite {
public:
    const char* name;         // ��Ʒ������
    const char* imagePath;    // ��Ʒ��ͼ��·��
    int quantity;             // ��Ʒ������
    bool isEdible;                // �Ƿ��ʳ��

    // Ĭ�Ϲ��캯��
    Item()
        : name(nullptr), imagePath(nullptr), quantity(0), isEdible(false) {}

    static Item* create(const FishInfo& fish_info);

    // ��ʼ������
    bool init(const FishInfo& fish_info);

    // ������Ʒ����
    void addQuantity(int count);

    // ������Ʒ������ʾ
    void updateQuantityDisplay();

    Item(const Item& other);

    Item& operator=(const Item& other);
    void increaseCount();
    bool isSameItem(const Item& other) const;
};

#endif // ITEM_H
