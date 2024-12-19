#ifndef __MARKETSTATE_H__
#define __MARKETSTATE_H__

#include "cocos2d.h"
#include "MarketItem.h"
#include "../DateManage/DateManage.h"
#include <vector>

/*
 * Class Name:     MarketState
 * Class Function: �г�������
 */
class MarketState {
public:
	// ��̬��������
	static MarketState* create();

	// �г��ĳ�ʼ��
	bool init();

	// �����洢�г�����������Ʒ
	std::vector<MarketItem> marketItems;

	// ������Ʒ
	void sellingItems();
private:
	// �����г���ÿ����Ʒ�ļ۸�
	void adjustItemPrice();
};

#endif // !__MARKETSTATE_H__
