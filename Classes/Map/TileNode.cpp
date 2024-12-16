#include "TileNode.h"
#include <algorithm>

// TileNode���ࣺ���캯��
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID) :
	position(position), tileType(tileType), currentGID(currentGID) {
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
cocos2d::Vec2 TileNode::getPosition() const {
	return position;
}

// Grass�ࣺ���캯��
Grass::Grass(const cocos2d::Vec2& position,const int& GID) :
	TileNode(position, TileType::Grass, GID) {
}

// Soil�ࣺ���캯��
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Soil, SOIL_GID), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}

// Soil�ࣺ����
void Soil::hoe() {
	isHoed = true;
}

// Soil�ࣺ��ˮ
void Soil::water() {
	if (isHoed ) {
		waterLevel = 10;
		isWatered = true;
	}
}

// Soil�ࣺʩ��
void Soil::fertilize() {

	// ���Ѿ���ֲ����ʱ����ʩ��
	if (crop) {
		fertilizeLevel = 10;
		isFertilized = true;

	}
}

// Soil�ࣺ��ֲ
void Soil::plantCrop(const std::string& seedName) {
	// δ���Ѻ��Ѿ���ֲ�Ļ�����
	if (isHoed == false || crop != nullptr) {
		return;
	}

	// �������ӵ�����ֲ�ͬ������
	if (seedName == "appleSeed") {
		crop = new Apple(getPosition());
	}
	else if (seedName == "cornSeed") {
		crop = new Corn(getPosition());
	}
	else if (seedName == "carrotSeed") {
		crop = new Carrot(getPosition());
	}
}

// Soil�ࣺ�ջ�
void Soil::harvest() {
	// �д����� ��Ҫ����
}

// ��������ʱ��仯�ĸ��º���
void Soil::gidUpdateByTime() {
	if (crop == nullptr) {
		return;
	}
	else {
		crop->grow();
		currentGID = crop->getCurrentGID();
	}
}

// Soil�ࣺ���¼��仯�ĸ��º���
void Soil::gidUpdateByEvent() {
	if (isHoed == false) {
		currentGID = SOIL_GID;
	}
	else {
		if (isWatered) {
			if (crop == nullptr) {
				currentGID = WATER_SOIL_GID;
			}
			else {
				currentGID = crop->getCurrentGID();
			}
		}
		else {
			if (crop == nullptr) {
				currentGID = HOED_SOIL_GID;
			}
			else {
				currentGID = crop->getCurrentGID();
			}
		}
	}
}

int Water::waterResource = MAX_WATER_RESOURCE;

// Water�ࣺ���캯��
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Water, WATER_GID){}

// Water�ࣺ�ж�ˮ��Դ
bool Water::isWaterDepleted() const {
	return waterResource == 0;
}

// Water�ࣺ��ˮ
void Water::pumpWater(int water) {
	waterResource -= water;
}

// Water�ࣺ���겹��ˮ��Դ
void Water::rechargeWaterResource() {
	waterResource = (waterResource+RANIY_REPLENISH)<MAX_WATER_RESOURCE ? waterResource+RANIY_REPLENISH:MAX_WATER_RESOURCE;
}

// Water�ࣺ��õ�ǰˮ��Դ
int Water::getCurrentWaterResource() const {
	return waterResource;
}

// Water�ࣺ��ʱ��仯
void Water::gidUpdateByTime() {
	// �жϵ�ǰˮ��Դ�Ƿ�ݽ�
	if (waterResource) {
		currentGID = WATER_GID;
	}
}

// Water�ࣺ��ʱ��仯
void Water::gidUpdateByEvent() {
	// �жϵ�ǰˮ��Դ�Ƿ�ݽ�
	if (waterResource == 0) {
		currentGID = SOIL_GID;
	}
}

// Obstacle�ࣺ���캯��
Obstacle::Obstacle(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Obstacle, 100)
{}

// Stone�ࣺ���캯��
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Stone, STONE_GID),stoneSolidity(3)
{}

// Stone�ࣺ�û�ʯͷ
void Stone::knockRock() {
	stoneSolidity--;
}

// Stone�ࣺ�ж��Ƿ����
bool Stone::isBroken() const{
	return stoneSolidity == 0;
}

// Mold�ࣺ���캯��
Mold::Mold(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Mold, 200)
{}