/****************************************************************
 * File Function: �ߵ����ʵ�֣�ʵ��ÿ���ߵ�ľ��幦��
 * Author:        ����
 ****************************************************************/
#include "TileNode.h"
#include "../Crop/Crop.h"
#include "../Crop/DogbaneCrop.h"
#include "../Crop/CornCrop.h"
#include "../Crop/CarrotCrop.h"
#include "../Bag/Bag.h"
#include "../Food/DogbaneFood.h"
#include "../Food/CornFood.h"
#include "../Food/CarrotFood.h"
#include <algorithm>

// TileNode���ࣺ���캯��
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType) :
	position(position), tileType(tileType){

}

// ��ʼ��
bool TileNode::init() {
	return true;
}

// ��ȡ�ýڵ������
TileType TileNode::getTileType() const {
	return tileType;
}

// ���ظ��������GID
int TileNode::getCurrentGID() const {
	return currentGID;
}

// TileNode���ࣺ��ȡλ��
cocos2d::Vec2 TileNode::getNodePosition() const {
	return position;
}

// TileNode���ࣺ����GID
void TileNode::updateGID() {
}

// Grass�ࣺ��̬��������
Grass* Grass::create(const cocos2d::Vec2& position) {
	Grass* grass = new (std::nothrow) Grass(position);
	if (grass&&grass->init()) {
		return grass;
	}
	CC_SAFE_DELETE(grass);
	return nullptr;
}

// Grass��ĳ�ʼ��
bool Grass::init() {
	currentGID = GRASS_GID;
	return true;
}

// Grass�ࣺ���캯��
Grass::Grass(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Grass) {
}

// Soil�ࣺ��̬���캯��
Soil* Soil::create(const cocos2d::Vec2& position) {
	Soil* soil = new (std::nothrow) Soil(position);
	if (soil&&soil->init()) {
		return soil;
	}
	CC_SAFE_DELETE(soil);
	return nullptr;
}

// Soil���ʼ��
bool Soil::init() {
	crop = nullptr;
	waterLevel = 0;
	fertilizeLevel = 0;
	isHoed = false;
	currentGID = SOIL_GID;
	return true;
}

// Soil�ࣺ���캯��
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Soil){
}

// Soil�ࣺ����
void Soil::soilHoe() {
	// ���ػ��߳�ȥ��������
	if (crop == nullptr) {
		isHoed = true;
	}
	else {
		// �����ǰ��������
		if (crop->isDead()) {
			delete crop;
			crop = nullptr;
		}
	}
	updateGID();
}

// Soil�ࣺ��ˮ
void Soil::soilWater() {
	waterLevel = 10;
}

// Soil�ࣺʩ��
void Soil::soilFertilize() {
	fertilizeLevel = 10;
}

// Soil�ࣺ��ֲ
void Soil::plantCrop(std::string seedName) {
	// ��ֲ���ȿ���
	if (isHoed&&crop==nullptr) {
		if (seedName == "dogbaneSeed") {				// ��ֲ�����
			crop = Dogbane::create();
		}
		else if (seedName == "cornSeed") {				// ��ֲ����
			crop = Corn::create();
		}
		else {											// ��ֲ���ܲ�
			crop = Carrot::create();
		}
		updateGID();
		crop->soilInfluence(waterLevel,fertilizeLevel);
	}
}

// Soil�ࣺӦ��ũҩ
void Soil::applyAgrochemical() {
	// �����ǰ�������ֱ�ӷ���
	if (crop == nullptr) {
		return;
	}

	// Ӧ��ũҩ
	crop->applyPesticide();
}

// Soil�ࣺ�ж��Ƿ�������
bool Soil::isPlanted() const {
	return crop != nullptr;
}

// Soil�ࣺ��������
void Soil::cropGrow() {
	// ��ȡ��������
	CropType cropType = crop->getCropType();
	
	// �����������
	switch (cropType) {
	case CropType::Dogbane:
		dynamic_cast<Dogbane*>(crop)->grow();
		break;
	case CropType::Corn:
		dynamic_cast<Corn*>(crop)->grow();
		break;
	case CropType::Carrot:
		dynamic_cast<Carrot*>(crop)->grow();
		break;
	}

	// ��������ͼ��
	updateGID();
}

// Soil�ࣺ�ջ�
void Soil::harvest() {
	// �ж������Ƿ����
	if (crop != nullptr && crop->isMature()) {
		Bag* bag = Bag::getInstance();
		CropType cropType = crop->getCropType();
		
		// �����������
		Food* harvestFood = nullptr;
		switch (cropType) {
		case CropType::Dogbane:
			harvestFood = DogbaneFood::create();
			break;
		case CropType::Corn:
			harvestFood = CornFood::create();
			break;
		case CropType::Carrot:
			harvestFood = CarrotFood::create();
			break;
		}

		// ���������Ʒ
		bag->addItem(harvestFood);

		// ɾ����ͼ�ϵ�����
		delete crop;
		crop = nullptr;

		// ����ͼ��
		updateGID();
	}
}

// Soil�ࣺʱ�����
void Soil::updateByTime() {
	// ��ˮ���½�
	if (waterLevel) {
		waterLevel--;
	}

	// �������½�
	if (fertilizeLevel){
		fertilizeLevel--;
	}

	// �������
	if (crop) {
		cropGrow();
		crop->soilInfluence(waterLevel, fertilizeLevel);
	}

	// ����ͼ��
	updateGID();
}

// Soil�ࣺ����GID
void Soil::updateGID() {
	// �����Ƿ�����������ж�
	if (crop == nullptr) {
		// �ж��Ƿ����
		if (isHoed == false) {
			currentGID = SOIL_GID;
			return;
		}

		// �ж�ˮ	
		if(waterLevel>0){
			currentGID = WATER_SOIL_GID;
			return;
		}

		// �жϷ���
		if (fertilizeLevel > 0) {
			currentGID = FERTILIZED_SOIL_GID;
			return;
		}

		// ��ˮ�����
		if (waterLevel == 0 && fertilizeLevel == 0) {
			currentGID = HOED_SOIL_GID;
		}
	}
	else {
		
		// ���ֲ��״̬
		CropType cropType = crop->getCropType();
		int cropGrowthStage = crop->getGrowthStage();

		// ��������
		if (cropGrowthStage == 0) {
			currentGID = DEAD_CROP;
			return;
		}

		// ֲ���������
		switch (cropType) {
		case CropType::Dogbane:
			currentGID = judgeDogbaneGID(cropGrowthStage);
			break;
		case CropType::Corn:
			currentGID = judgeCornGID(cropGrowthStage);
			break;
		case CropType::Carrot:
			currentGID = judgeCarrotGID(cropGrowthStage);
			break;
		}
	}
}

// �����GID�ж�
int Soil::judgeDogbaneGID(int growStage) {
	// ��ͬ�����׶�
	if (growStage == 1) {										// Dogbane�����׶�1
		// �ж�ˮ�ͷ���
		if (waterLevel && fertilizeLevel) {
			return DOGBANE_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return DOGBANE_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return DOGBANE_FIRST_FERTILIZE;
		}
		else {
			return DOGBANE_FIRST;
		}
	}
	else if (growStage == 2) {								// Dogbane�����׶�2
		// �ж�ˮ�ͷ���
		if (waterLevel && fertilizeLevel) {
			return DOGBANE_SECOND_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return DOGBANE_SECOND_WATER;
		}
		else if (fertilizeLevel) {
			return DOGBANE_SECOND_FERTILIZE;
		}
		else {
			return DOGBANE_SECOND;
		}
	}
	else if (growStage == 3) {								// Dogbane�����׶�3
		// �жϳ溦
		if (crop->judgeInfested()) {
			return DOGBANE_THIRD_ILL;
		}
		else {
			// �ж�ˮ�ͷ���
			if (waterLevel && fertilizeLevel) {
				return DOGBANE_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return DOGBANE_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return DOGBANE_THIRD_FERTILIZE;
			}
			else {
				return DOGBANE_THIRD;
			}
		}
	}
	else {															// Dogbane�����׶���
		// �жϳ溦
		if (crop->judgeInfested()) {
			return DOGBANE_THIRD_ILL;
		}
		else {
			// �ж�ˮ�ͷ���
			if (waterLevel && fertilizeLevel) {
				return DOGBANE_FOURTH_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return DOGBANE_FOURTH_WATER;
			}
			else if (fertilizeLevel) {
				return DOGBANE_FOURTH_FERTILIZE;
			}
			else {
				return DOGBANE_FOURTH;
			}
		}
	}
}

// ����GID�ж�
int Soil::judgeCornGID(int growStage) {
	// ��ͬ�����׶�
	if (growStage == 1) {									// Corn�����׶�1
		// �ж�ˮ�ͷ���
		if (waterLevel && fertilizeLevel) {
			return CORN_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return CORN_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return CORN_FIRST_FERTILIZE;
		}
		else {
			return CORN_FIRST;
		}
	}
	else if (growStage == 2) {								// Corn�����׶�2
		// �ж��Ƿ��г溦
		if (crop->judgeInfested()) {
			return CORN_SECOND_ILL;
		}
		else{
			if (waterLevel && fertilizeLevel) {
				return CORN_SECOND_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CORN_SECOND_WATER;
			}
			else if (fertilizeLevel) {
				return CORN_SECOND_FERTILIZE;
			}
			else {
				return CORN_SECOND;
			}
		}
	}
	else {													// Corn�����׶�3
		// �ж��Ƿ��г溦
		if (crop->judgeInfested()) {
			return CORN_THIRD_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CORN_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CORN_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return CORN_THIRD_FERTILIZE;
			}
			else {
				return CORN_THIRD;
			}
		}
	}
}

// ���ܲ�GID�ж�
int Soil::judgeCarrotGID(int growStage) {
	// ��ͬ�����׶�
	if (growStage == 1) {									// Carrot�����׶�1
		// �ж�ˮ�ͷ���
		if (waterLevel && fertilizeLevel) {
			return CARROT_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return CARROT_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return CARROT_FIRST_FERTILIZE;
		}
		else {
			return CARROT_FIRST;
		}
	}
	else if (growStage == 2) {								// Carrot�����׶�2
		// �ж��Ƿ��г溦
		if (crop->judgeInfested()) {
			return CARROT_SECOND_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CARROT_SECOND_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CARROT_SECOND_WATER;
			}
			else if (fertilizeLevel) {
				return CARROT_SECOND_FERTILIZE;
			}
			else {
				return CARROT_SECOND;
			}
		}
	}
	else {													// Corn�����׶�3
		// �ж��Ƿ��г溦
		if (crop->judgeInfested()) {
			return CARROT_THIRD_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CARROT_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CARROT_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return CARROT_THIRD_FERTILIZE;
			}
			else {
				return CARROT_THIRD;
			}
		}
	}
}

// Water�ࣺ��̬��������
Water* Water::create(const cocos2d::Vec2& position) {
	Water* water = new (std::nothrow) Water(position);
	if (water&&water->init()) {
		return water;
	}
	CC_SAFE_DELETE(water);
	return nullptr;
}

// Water�ࣺ��ʼ��
bool Water::init() {
	currentGID = WATER_GID;
	return true;
}

// Water�๹�캯��
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Water){
}

// Obstacle�ࣺ��̬��������
Obstacle* Obstacle::create(const cocos2d::Vec2& position) {
	Obstacle* obstacle = new (std::nothrow) Obstacle(position);
	if (obstacle && obstacle->init()){
		return obstacle;
	}
	CC_SAFE_DELETE(obstacle);
	return nullptr;
}

// Obstacle�ࣺ��ʼ��
bool Obstacle::init() {
	currentGID = OBSTACLES_GID;
	return true;
}

// Obstacle�ࣺ���캯��
Obstacle::Obstacle(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Obstacle){
}

// Stone�ࣺ��̬��������
Stone* Stone::create(const cocos2d::Vec2& position) {
	Stone* stone = new (std::nothrow) Stone(position);
	if (stone && stone->init()) {
		return stone;
	}
	CC_SAFE_DELETE(stone);
	return nullptr;
}

// Obstacle�ࣺ��ʼ��
bool Stone::init() {
	currentGID = STONE_GID;
	stoneSolidity = 3;
	return true;
}

// Stone�ࣺ���캯��
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Stone){
}

// Stone�ࣺ�û�ʯͷ
void Stone::knockRock() {
	stoneSolidity--;
}

// Stone�ࣺ�ж��Ƿ����
bool Stone::isBroken() const{
	return stoneSolidity == 0;
}

// Mold�ࣺ��̬��������
Mold* Mold::create(const cocos2d::Vec2& position) {
	Mold* mold = new (std::nothrow) Mold(position);
	if (mold && mold->init()) {
		return mold;
	}
	CC_SAFE_DELETE(mold);
	return nullptr;
}

// Obstacle�ࣺ��ʼ��
bool Mold::init() {
	currentGID = MOLD_GID;
	return true;
}

// Mold�ࣺ���캯��
Mold::Mold(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Mold){
}