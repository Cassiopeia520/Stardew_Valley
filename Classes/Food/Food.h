/****************************************************************
 * File Function: ʳ���࣬��һ��������࣬�̳�Item�࣬�ܹ����뱳����ͬʱ���Խ������
 * Author:        Τ���
 ****************************************************************/
#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "../Item/Item.h"
#include "../Constant/Constant.h"

class Food : public Item {
public:
    // ��̬��������
    static Food* create(const ItemInfo& item_info);

    // ��ʼ������
    virtual bool init(const ItemInfo& item_info) override;

    // ��дʹ����Ʒ
    virtual void useItem() override {};

    // ��������
    virtual ~Food() {}
};

#endif // ITEM_H
