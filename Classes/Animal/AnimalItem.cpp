#include "AnimalItem.h"
#include "../Map/FarmMap.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// AnimalItem�ࣺ��ʼ��
bool AnimalItem::init(const ItemInfo& item_info) {
	itemName = (std::string)item_info.name;
	itemImage = (std::string)item_info.image;
	return Sprite::initWithFile(item_info.image);
}

// CowItem��̬��������
CowItem* CowItem::create() {
	CowItem* cowItem = new(std::nothrow) CowItem();
	if (cowItem && cowItem->init()) {
		cowItem->autorelease();
		return cowItem;
	}
	CC_SAFE_DELETE(cowItem);
	return nullptr;
}

// ��ʼ��
bool CowItem ::init() {
	// ���û���ĳ�ʼ������
	return AnimalItem::init(COW_ITEM);
}

// ʹ�ù���
void CowItem::useItem() {

}

// CowItem��̬��������
SheepItem* SheepItem::create() {
	SheepItem* sheepItem = new(std::nothrow) SheepItem();
	if (sheepItem && sheepItem->init()) {
		sheepItem->autorelease();
		return sheepItem;
	}
	CC_SAFE_DELETE(sheepItem);
	return nullptr;
}

// ��ʼ��
bool SheepItem::init() {
	// ���û���ĳ�ʼ������
	return AnimalItem::init(SHEEP_ITEM);
}

// ʹ�ù���
void SheepItem::useItem() {

}

// CowItem��̬��������
ChickenItem* ChickenItem::create() {
	ChickenItem* chickenItem = new(std::nothrow) ChickenItem();
	if (chickenItem && chickenItem->init()) {
		chickenItem->autorelease();
		return chickenItem;
	}
	CC_SAFE_DELETE(chickenItem);
	return nullptr;
}

// ��ʼ��
bool ChickenItem::init() {
	// ���û���ĳ�ʼ������
	return AnimalItem::init(CHICKEN_ITEM);
}

// ʹ�ù���
void ChickenItem::useItem() {

}

// CowItem��̬��������
PigItem* PigItem::create() {
	PigItem* pigItem = new(std::nothrow) PigItem();
	if (pigItem && pigItem->init()) {
		pigItem->autorelease();
		return pigItem;
	}
	CC_SAFE_DELETE(pigItem);
	return nullptr;
}

// ��ʼ��
bool PigItem::init() {
	// ���û���ĳ�ʼ������
	return AnimalItem::init(PIG_ITEM);
}

// ʹ�ù���
void PigItem::useItem() {

}