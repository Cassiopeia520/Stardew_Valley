#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h"
#include <string>

class Item : public cocos2d::Sprite {
public:
    std::string name;         // ��Ʒ������
    std::string imagePath;    // ��Ʒ��ͼ��·��
    int quantity;             // ��Ʒ������

    // ���캯��
    Item(const std::string& itemName, const std::string& itemImagePath, int itemQuantity = 1);

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
