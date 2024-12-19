#ifndef __MARKET_ITEM_H__
#define __MARKET_ITEM_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <string>

/*
 * Class Function: �г���Ʒ��
 */
class MarketGood {
public:
	// ��̬��������
	static MarketGood* create(MarketGoodLabel* good);

	// ��ʼ��
	bool init(std::string name, int price);

	// �����۸�
	void adjustPrice();

	// ��ȡ��Ʒ����
	std::string getGoodName() const;

	// ��ȡ��Ʒ�۸�
	int getGoodPrice() const;
private:
	std::string marketGoodName;				// ��Ʒ����
	int basePrice;							// �����۸�
	int currentPrice;						// ���ڵļ۸�
};

#endif // !__MARKET_ITEM_H__
