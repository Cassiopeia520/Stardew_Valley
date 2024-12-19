#ifndef __MARKETSTATE_H__
#define __MARKETSTATE_H__

#include "cocos2d.h"
#include "MarketGood.h"
#include "../Date/DateManage.h"
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
	std::vector<MarketGood*> marketGoods;

	// ������Ʒ
	int sellingGoods(const std::string& goodName);
private:
	// �����г���ÿ����Ʒ�ļ۸�
	void adjustGoodPrice();
};

#endif // !__MARKETSTATE_H__
