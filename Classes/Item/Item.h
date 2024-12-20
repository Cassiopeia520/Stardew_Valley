/****************************************************************
 * File Function: ��Ʒ�࣬������࣬���ڷ��뱳����
 * Author:        ��׿�� Τ���
 ****************************************************************/
#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <string>

// ��Ʒ�࣬��һ��������
class Item : public cocos2d::Sprite {
public:
	// ��ʼ�������麯�����������ʵ�֣�
	virtual bool init(const ItemInfo& item_info) = 0;

	// ʹ����Ʒ�����麯�����������ʵ�֣�
	virtual void useItem() = 0;

	// ��ȡ�������ƣ�����������ֱ��ʵ��
	std::string getItemName() const {
		return itemName;
	}

	//��ȡͼƬλ��
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
