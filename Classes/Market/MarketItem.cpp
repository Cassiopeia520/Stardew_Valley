#include "MarketItem.h"
#include "../DateManage/DateManage.h"
#include <string>

// ��̬��������
MarketItem* MarketItem::create(std::string name, int price) {
	MarketItem* marketItem = new (std::nothrow) MarketItem();
	if (marketItem && marketItem->init(name,price)) {
		return marketItem;
	}

	CC_SAFE_DELETE(marketItem);
	return nullptr;
}

// ��ʼ��
bool MarketItem::init(std::string name, int price) {
	marketItemName = name;
	basePrice = price;
	currentPrice = price;
	return true;
}

// ��̬�����۸�
void MarketItem::adjustPrice() {

}