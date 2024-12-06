#include "Crop.h"

// Crop���ࣺ���캯��
Crop::Crop(const CropType& cropType, const int& maxGrowthDay, const int& cropGID, cocos2d::Vec2 position) :
	cropType(cropType), maxGrowthDay(maxGrowthDay), growthStage(0),
	isInfested(false), isDrought(false), isFertilized(false),
	cropGID(cropGID), position(position), infestedDay(0), 
	droughtDay(0) {}

// Crop���ࣺ��ˮ
void Crop::irrigate() {

	isDrought = false;
	droughtDay = 0;
}

// Crop���ࣺʩ��
void Crop::fertilize() {
	isFertilized = true;
}

// Crop���ࣺ��ȡ�ɳ�����Ҫ������
int Crop::getMaturedDay() const {
	return maxGrowthDay;
}

// Crop���ࣺ�ж��Ƿ����
bool Crop::isMature() const{

	// �Ѿ����������������Ҫ�������Լ���ʱ����
	if (growedDay >= getMaturedDay() && growedDay <= maxAliveDay) {
		return true;
	}
	return false;
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

// Apple���ࣺ���캯��
Apple::Apple(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 28, 34, position) {
	season.push_back(Season::SPRING);
	season.push_back(Season::SUMMER);
	season.push_back(Season::AUTUMN);
}

// Apple���ࣺ��������
void Apple::grow() {

	// �ж��Ƿ�ȱˮ�������ܳ溦
	if (isDrought || isInfested) {
		return;
	}
	
	// �ж��Ƿ���ʩ��
	if (isFertilized) {
		growedDay += 2;
	}
	else {
		growedDay += 1;
	}

	if (growedDay >= 0 && growedDay <= getMaturedDay() / 3) {
		growthStage = 1;
		this->updateGID();
	}
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

// Corn���ࣺ���캯��
Corn::Corn(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 36, 34, position) {
	season.push_back(Season::SPRING);
	season.push_back(Season::SUMMER);
}

// Carrot���ࣺ���캯��
Carrot::Carrot(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 40, 34, position) {
	season.push_back(Season::SPRING);
}

