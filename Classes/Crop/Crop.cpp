#include "Crop.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

// Crop���ࣺ���캯��
Crop::Crop(const CropType& cropType) :
	cropType(cropType), growthStage(1),
	isInfested(false), isDrought(false), isFertilized(false),
	infestedDay(0), droughtDay(0),growedDay(0) {
}

// �����������Ӱ��
void Crop::soilInfluence(int waterLevel,int fertilizeLevel) {
	// ������ˮ
	if (waterLevel) {
		isDrought = false;
		droughtDay = 0;
	}
	else {
		isDrought = true;
	}

	// ��������
	if (fertilizeLevel) {
		isFertilized = true;
	}
	else {
		isFertilized = false;
	}
}

// ��ʼ��
bool Crop::init() {
	return true;
}

// �ж�����
bool Crop::isDead() {
	return growthStage == 0;
}

// �ж��������
bool Crop::isMature() {
	switch (cropType){
	case CropType::Dogbane:
		return growthStage == DOGBANE_MAX_GROWTH_STAGE;
		break;
	case CropType::Corn:
		return growthStage == CORN_MAX_GROWTH_STAGE;
		break;
	case CropType::Carrot:
		return growthStage == CARROT_MAX_GROWTH_STAGE;
		break;
	}
}

// ʹ��ũҩ
void Crop::applyPesticide() {
	isInfested = false;
	infestedDay = 0;
}

// ���������׶�
void Crop::updateGrowthStage() {
	// ��ü���
	DateManage* dateManage = DateManage::getInstance();
	std::string currentSeason = dateManage->getCurrentSeason();

	if (isDead()) {
		return;
	}

	// ��ʼ�����׶�Ϊ1
	growthStage = 1;

	// �ж������׶�
	int totalDays = 0;
	for (int index = 0; index < static_cast<int>(seasonalGrowthStageDay[currentSeason].size()); index++) {
		totalDays += seasonalGrowthStageDay[currentSeason][index];
		if (totalDays > growedDay) {
			break;
		}
		growthStage ++;
	}
	CCLOG("%d",growthStage);
	dateManage = nullptr;
}

// ��ȡ�����׶�
int Crop::getGrowthStage() const {
	return growthStage;
}

// �ж�����溦
bool Crop::judgeInfested() const {
	return isInfested == true;
}

// ��õ�ǰ��������
CropType Crop::getCropType() const {
	return cropType;
}
