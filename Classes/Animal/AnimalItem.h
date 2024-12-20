/****************************************************************
 * File Function: ������Ʒ�࣬ţ����������ı�����Ʒ
 * Author:        ����
 ****************************************************************/
#ifndef __AnimalItem_H__
#define __AnimalItem_H__

#include "cocos2d.h"
#include "../Item/Item.h"

// AnimalItem�ࣺ��ʾ�����еĶ���
class AnimalItem : public Item {
public:
	// ��ʼ��
	virtual bool init(const ItemInfo& item_info) override;

	// ʹ�ù���
	// virtual void useItem() override;

	virtual ~AnimalItem() {}
};

// CowItem��
class CowItem : public AnimalItem {
public:
	// ��̬��������
	static CowItem* create();

	// ��ʼ����ţ��Ʒ
	bool init();

	// ʹ�ù���
	void useItem() override;
};

// SheepItem��
class SheepItem : public AnimalItem {
public:
	// ��̬��������
	static SheepItem* create();

	// ��ʼ������Ʒ
	bool init();

	// ʹ�ù���
	void useItem() override;
};

// ChickenItem��
class ChickenItem : public AnimalItem {
public:
	// ��̬��������
	static ChickenItem* create();

	// ��ʼ������Ʒ
	bool init();

	// ʹ�ù���
	void useItem() override;
};

// PigItem��
class PigItem : public AnimalItem {
public:
	// ��̬��������
	static PigItem* create();

	// ��ʼ������Ʒ
	bool init();

	// ʹ�ù���
	void useItem() override;
};
#endif