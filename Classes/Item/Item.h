/****************************************************************
 * File Function: ʵ����Ʒ�࣬��һ��������࣬��Ʒ��װ�ڱ�����
 * Author:        ��׿�� Τ���
 ****************************************************************/

#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <string>

// ��Ʒ��
class Item : public cocos2d::Sprite {
public:
	// ��ʼ��
	virtual bool init(const ItemInfo& item_info) = 0;

	// ʹ����Ʒ
	virtual void useItem() = 0;

	// ��ȡ��������
	std::string getItemName() const {
		return itemName;
	}

	// ��ȡͼƬλ��
	std::string getItemImage() const {
		return itemImage;
	}

	// ����������
	virtual ~Item() {}
protected:
	// ����
	std::string itemName;

	// ͼƬλ��
	std::string itemImage;
};
#endif