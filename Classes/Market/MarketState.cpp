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
	return true;
}

// ������Ʒ
void MarketState::sellingItems() {

}

// �����г���ÿ����Ʒ�ļ۸�
void MarketState::adjustItemPrice() {

}