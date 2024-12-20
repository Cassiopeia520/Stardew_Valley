/****************************************************************
 * File Function: �����������ʵ�֣�ʵ�����������ڲ�ͬ�����µ�����
 * Author:        ����
 ****************************************************************/
#include "CornCrop.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

// ��̬��������
Corn* Corn::create() {
	Corn* corn = new (std::nothrow) Corn();
	if (corn && corn->init()) {
		return corn;
	}
	CC_SAFE_DELETE(corn);
	return nullptr;
}

// ��ʼ��
bool Corn::init() {
	// ��ʼ����ͬ���ڵ������׶�����
	seasonalGrowthStageDay["Spring"].push_back(CORN_SPRING_STAGE_FIRST);
	seasonalGrowthStageDay["Spring"].push_back(CORN_SPRING_STAGE_SECOND);
	seasonalGrowthStageDay["Summer"].push_back(CORN_SUMMER_STAGE_FIRST);
	seasonalGrowthStageDay["Summer"].push_back(CORN_SUMMER_STAGE_SECOND);
	seasonalGrowthStageDay["Fall"].push_back(CORN_AUTUMN_STAGE_FIRST);
	seasonalGrowthStageDay["Fall"].push_back(CORN_AUTUMN_STAGE_SECOND);
	seasonalGrowthStageDay["Winter"].push_back(CORN_WINTER_STAGE_FIRST);
	seasonalGrowthStageDay["Winter"].push_back(CORN_WINTER_STAGE_SECOND);
	return true;
}

// ���캯��
Corn::Corn() :
	Crop(CropType::Corn) {
}

// ��������
void Corn::grow() {
	// �ж��Ƿ�ɺ��Լ��溦
	if (isDrought == false && isInfested == false) {
		if (isFertilized) {
			growedDay += 2;
		}
		else {
			growedDay++;
		}
	}
	
	// �ɺ���������
	if (isDrought) {
		droughtDay++;
	}

	// ������������
	if (isInfested) {
		infestedDay++;
	}

	// �жϸɺ����߳溦�����Ƿ񳬹���������
	if (droughtDay > WATER_SCARCITY_DAY || infestedDay > INFESTED_DAY) {
		growthStage = 0;				// ��������
		return;
	}

	// ������ɲ���
	if (isInfested == false) {
		generatePest();
	}

	// �������������׶�
	updateGrowthStage();
}

// ������ɲ���
void Corn::generatePest() {
	// ��õ�ǰ����������
	DateManage* dateManage = DateManage::getInstance();
	std::string season = dateManage->getCurrentSeason();
	Weather weather = dateManage->getCurrentWeather();

	// ǰ���������׶β����������
	if (growthStage == 0 || growthStage == 1 || growthStage == 2) {
		return;
	}

	// �����溦����
	int basePestProbability = 0;

	// ���ݼ��ڻ�û����溦����
	if (season == "Spring") {
		basePestProbability = CORN_SPRING_PEST_PROBABILITY;
	}
	else if (season == "Summer") {
		basePestProbability = CORN_SUMMER_PEST_PROBABILITY;
	}
	else if (season == "Fall") {
		basePestProbability = CORN_AUTUMN_PEST_PROBABILITY;
	}
	else {
		basePestProbability = CORN_WINTER_PEST_PROBABILITY;
	}

	// �����������ӳ溦����
	switch (weather) {
	case Weather::Sunny:
		basePestProbability -= 5;
		break;
	case Weather::LightRain:
		basePestProbability += 5;
		break;
	case Weather::HeavyRain:
		basePestProbability += 10;
		break;
	}

	// ������ɲ���
	isInfested = (std::rand() % 100) < basePestProbability;
}