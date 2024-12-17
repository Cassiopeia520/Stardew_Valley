#include "CarrotCrop.h"
#include "../DateManage/DateManage.h"
#include "../Constant/Constant.h"

Carrot* Carrot::create() {
	Carrot* carrot = new (std::nothrow) Carrot();
	if (carrot && carrot->init()) {
		return carrot;
	}
	CC_SAFE_DELETE(carrot);
	return nullptr;
}

bool Carrot::init() {
	// ��ʼ����ͬ���ڵ������׶�����
	seasonalGrowthStageDay["Spring"].push_back(CARROT_SPRING_STAGE_FIRST);
	seasonalGrowthStageDay["Spring"].push_back(CARROT_SPRING_STAGE_SECOND);
	seasonalGrowthStageDay["Summer"].push_back(CARROT_SUMMER_STAGE_FIRST);
	seasonalGrowthStageDay["Summer"].push_back(CARROT_SUMMER_STAGE_SECOND);
	seasonalGrowthStageDay["Fall"].push_back(CARROT_AUTUMN_STAGE_FIRST);
	seasonalGrowthStageDay["Fall"].push_back(CARROT_AUTUMN_STAGE_SECOND);
	seasonalGrowthStageDay["Winter"].push_back(CARROT_WINTER_STAGE_FIRST);
	seasonalGrowthStageDay["Winter"].push_back(CARROT_WINTER_STAGE_SECOND);
	return true;
}


// ���캯��
Carrot::Carrot() :
	Crop(CropType::Carrot) {
}

// ��������
void Carrot::grow() {
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

	// ���µ�ǰ�����׶�
	updateGrowthStage();
}

// ������ɲ���
void Carrot::generatePest() {
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
		basePestProbability = CARROT_SPRING_PEST_PROBABILITY;
	}
	else if (season == "Summer") {
		basePestProbability = CARROT_SUMMER_PEST_PROBABILITY;
	}
	else if (season == "Fall") {
		basePestProbability = CARROT_AUTUMN_PEST_PROBABILITY;
	}
	else {
		basePestProbability = CARROT_WINTER_PEST_PROBABILITY;
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