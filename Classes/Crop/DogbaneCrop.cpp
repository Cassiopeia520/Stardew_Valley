/****************************************************************
 * File Function: ������������ʵ�֣�ʵ�ַ���������ڲ�ͬ�����µ�����
 * Author:        ����
 ****************************************************************/
#include "cocos2d.h"
#include "DogbaneCrop.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

// ��̬��������
Dogbane* Dogbane::create() {
	Dogbane* dogbane = new (std::nothrow) Dogbane();
	if (dogbane && dogbane->init()) {
		return dogbane;
	}
	CC_SAFE_DELETE(dogbane);
	return nullptr;
}

// ����ݵĳ�ʼ��
bool Dogbane::init() {
	// ��ʼ����ͬ���ڵ������׶�����
	seasonalGrowthStageDay["Spring"].push_back(DOGBANE_SPRING_STAGE_FIRST);
	seasonalGrowthStageDay["Spring"].push_back(DOGBANE_SPRING_STAGE_SECOND);
	seasonalGrowthStageDay["Spring"].push_back(DOGBANE_SPRING_STAGE_THIRD);
	seasonalGrowthStageDay["Summer"].push_back(DOGBANE_SUMMER_STAGE_FIRST);
	seasonalGrowthStageDay["Summer"].push_back(DOGBANE_SUMMER_STAGE_SECOND);
	seasonalGrowthStageDay["Summer"].push_back(DOGBANE_SUMMER_STAGE_THIRD);
	seasonalGrowthStageDay["Fall"].push_back(DOGBANE_AUTUMN_STAGE_FIRST);
	seasonalGrowthStageDay["Fall"].push_back(DOGBANE_AUTUMN_STAGE_SECOND);
	seasonalGrowthStageDay["Fall"].push_back(DOGBANE_AUTUMN_STAGE_THIRD);
	seasonalGrowthStageDay["Winter"].push_back(DOGBANE_WINTER_STAGE_FIRST);
	seasonalGrowthStageDay["Winter"].push_back(DOGBANE_WINTER_STAGE_SECOND);
	seasonalGrowthStageDay["Winter"].push_back(DOGBANE_WINTER_STAGE_THIRD);
	return true;
}

// ���캯��
Dogbane::Dogbane() :
	Crop(CropType::Dogbane) {
}

// ��������
void Dogbane::grow() {
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

	// ������������״̬
	updateGrowthStage();
}

// ������ɲ���
void Dogbane::generatePest() {
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
		basePestProbability = DOGBANE_SPRING_PEST_PROBABILITY;
	}
	else if (season == "Summer") {
		basePestProbability = DOGBANE_SUMMER_PEST_PROBABILITY;
	}
	else if (season == "Fall") {
		basePestProbability = DOGBANE_AUTUMN_PEST_PROBABILITY;
	}
	else {
		basePestProbability = DOGBANE_WINTER_PEST_PROBABILITY;
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