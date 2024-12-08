#include "Crop.h"

// Crop���ࣺ���캯��
Crop::Crop(const CropType& cropType,  const int& cropGID, cocos2d::Vec2 position) :
	cropType(cropType), growthStage(0),
	isInfested(false), isDrought(false), isFertilized(false),
	cropGID(cropGID), position(position), infestedDay(0), 
	droughtDay(0),growedDay(0) {
	switch (cropType) {
	case CropType::Apple:						// ƻ���ڲ�ͬ���ڵ���������
		seasonGrowDay[Season::Spring] = 4;
		seasonGrowDay[Season::Summer] = 3;
		seasonGrowDay[Season::Autumn] = 6;
		seasonGrowDay[Season::Winter] = 7;
		break;
	case CropType::Corn:						// �����ڲ�ͬ���ڵ���������
		seasonGrowDay[Season::Spring] = 5;
		seasonGrowDay[Season::Summer] = 4;
		seasonGrowDay[Season::Autumn] = 7;
		seasonGrowDay[Season::Winter] = 8;
		break;
	case CropType::Carrot:						// ���ܲ��ڲ�ͬ���ڵ���������
		seasonGrowDay[Season::Spring] = 6;
		seasonGrowDay[Season::Summer] = 5;
		seasonGrowDay[Season::Autumn] = 8;
		seasonGrowDay[Season::Winter] = 9;
		break;
	}
}

// Crop���ࣺ��ˮ
void Crop::irrigate() {

	isDrought = false;
	droughtDay = 0;
}

// Crop���ࣺʩ��
void Crop::fertilize() {
	isFertilized = true;
}

// Crop���ࣺʹ��ũҩ
void Crop::applyPesticide() {
	isInfested = false;
	infestedDay = 0;
}

// Crop���ࣺ��õ�ǰͼ���GID
int Crop::getCurrentGID() {
	return cropGID;
}

// Crop���ࣺ��õ�ǰ������������
int Crop::getCurrentSeasonGrowDay(Season season) {
	switch (season) {
	case Season::Spring:
		return seasonGrowDay[Season::Spring];
		break;
	case Season::Summer:
		return seasonGrowDay[Season::Summer];
		break;
	case Season::Autumn:
		return seasonGrowDay[Season::Autumn];
		break;
	case Season::Winter:
		return seasonGrowDay[Season::Winter];
		break;
	}
}

// Apple���ࣺ���캯��
Apple::Apple(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Apple, SEED_GID, position) {
}

// Apple���ࣺ���º�����д
void Apple::updateGID() {
	switch (growthStage) {
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	}
}

// Apple���ࣺgrow��������д
void Apple::grow() {
	// ������
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = APPLE_GID;
	}
}

// Corn���ࣺ���캯��
Corn::Corn(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Corn, SEED_GID, position) {
}

// Corn���ࣺgrow��������д
void Corn::grow() {
	// ������
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = CORN_GID;
	}
}

// Carrot���ࣺ���캯��
Carrot::Carrot(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Carrot,SEED_GID, position) {
}

// Carrot���ࣺ��������
void Carrot::grow() {
	// ������
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = CARROT_GID;
	}
}
