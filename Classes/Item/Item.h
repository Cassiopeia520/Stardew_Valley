#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"
#include <string>

// ��Ʒ�࣬��һ��������
class Item : public cocos2d::Sprite {
public:
	// ��ʼ��������ʵ�֣�
	virtual bool init(const std::string& name) = 0;

	// ʹ����Ʒ�����麯�����������ʵ�֣�
	virtual void useItem() = 0;

	// ��ȡ�������ƣ�����������ֱ��ʵ��
	std::string getItemName() const {
		return itemName;
	}

	// ����������
	virtual ~Item() {}
protected:
	// ��������
	std::string itemName;
};

#endif
