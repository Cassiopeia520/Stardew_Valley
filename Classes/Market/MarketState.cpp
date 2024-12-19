#include "MarketState.h"
#include "../Constant/Constant.h"
#include <string>

// ��̬��������
MarketState* MarketState::create() {
	MarketState* marketState = new (std::nothrow) MarketState();
	if (marketState && marketState->init()) {
		return marketState;
	}

	CC_SAFE_DELETE(marketState);
	return nullptr;
}

// ��ʼ��
bool MarketState::init() {
	// ���г��м�����Ʒ
	for (auto good : INIT_GOODS) {
		MarketGood* marketGood = MarketGood::create(&good);
		marketGoods.push_back(marketGood);
	}
	return true;
}

// ������Ʒ
int MarketState::sellingGoods(const std::string& goodName) {
	// �ȵ����г��е���Ʒ�۸�
	adjustGoodPrice();

	// �����г��ҵ��۸�
	for (auto good : marketGoods) {
		if (good->getGoodName() == goodName) {
			return good->getGoodPrice();
		}
	}

	// û�ҵ�����Ʒ
	return 0;
}

// �����г���ÿ����Ʒ�ļ۸�
void MarketState::adjustGoodPrice() {
	// �����г�����ÿ����Ʒ���м۸����
	for (auto good : marketGoods) {
		good->adjustPrice();
	}
}