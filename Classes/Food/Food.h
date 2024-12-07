#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "../Constant/Constant.h"

class Food : public cocos2d::Sprite {
public:
    const char* name;         // ��Ʒ������
    const char* imagePath;    // ��Ʒ��ͼ��·��
    int quantity;             // ��Ʒ������

    // Ĭ�Ϲ��캯��
    Food()
        : name(nullptr), imagePath(nullptr), quantity(0) {}

    static Food* create(const FishInfo& fish_info);

    // ��ʼ������
    bool init(const FishInfo& fish_info);

    // ������Ʒ����
    void addQuantity(int count);

    // ������Ʒ������ʾ
    void updateQuantityDisplay();

    Food(const Food& other);

    Food& operator=(const Food& other);
    void increaseCount();
    bool isSameItem(const Food& other) const;
};

#endif // ITEM_H
