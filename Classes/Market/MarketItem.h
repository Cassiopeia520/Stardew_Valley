#ifndef __MARKET_ITEM_H__
#define __MARKET_ITEM_H__

#include "cocos2d.h"
#include <string>

/*
 * Class Name:     MarketItem
 * Class Function: �г���Ʒ��
 */
class MarketItem {
public:
	std::string marketItemName;				// ��Ʒ����
	int basePrice;							// �����۸�
	int currentPrice;						// ���ڵļ۸�
	int supply;								// �����и���Ʒ������

	// ��̬��������
	static MarketItem* create(std::string name);

	// ��ʼ��
	bool init();

	// �����۸�
	void adjustPrice();
};

#endif // !__MARKET_ITEM_H__
