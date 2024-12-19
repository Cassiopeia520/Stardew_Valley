#include "MarketGood.h"
#include "../DateManage/DateManage.h"
#include <string>

// ��̬��������
MarketGood* MarketGood::create(MarketGoodLabel* good) {
	MarketGood* marketGood = new (std::nothrow) MarketGood();
	if (marketGood && marketGood->init(good->name,good->basePrice)) {
		return marketGood;
	}

	CC_SAFE_DELETE(marketGood);
	return nullptr;
}

// ��ʼ��
bool MarketGood::init(std::string name, int price) {
	// ��ʼ����Ʒ
	marketGoodName = name;
	basePrice = price;
	currentPrice = price;
	return true;
}

// ��̬�����۸�
void MarketGood::adjustPrice() {
	// ʯͷ�ļ۸�̶�����
	if (getGoodName() == "stoneItem") {
		return;
	}
	// ��ȡ��ǰ����������
	DateManage* dateManage = DateManage::getInstance();
	std::string season = dateManage->getCurrentSeason();
	Weather weather = dateManage->getCurrentWeather();

	// ���ڵ�Ӱ��
	if (season == "Spring") {
		currentPrice = basePrice;
	}
	else if (season == "Summer") {
		currentPrice = basePrice / 2;
	}
	else if (season == "Fall") {
		currentPrice = basePrice * 3 / 2;
	}
	else {
		currentPrice = basePrice * 2;
	}

	switch(weather){
	case Weather::Sunny:
		currentPrice += SUNNY_MONEY_INFLUENCE;
		break;
	case Weather::LightRain:
		currentPrice += LIGHTRAIN_MONEY_INFLUENCE;
		break;
	case Weather::HeavyRain:
		currentPrice += HEAVYRAIN_MONEY_INFLUENCE;
		break;
	case Weather::Snowy:
		currentPrice += SNOWY_MONEY_INFLUENCE;
		break;
	}
}

// ��ȡ��Ʒ����
std::string MarketGood::getGoodName() const {
	return marketGoodName;
}

// ��ȡ��Ʒ�۸�
int MarketGood::getGoodPrice() const {
	return currentPrice;
}