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

// TileNode���ࣺ����ͼ���GID
// ˼·����״̬ȥ����
void TileNode::updateGID() {
	return;
}

// Grass�ࣺ���캯��
Grass::Grass(const cocos2d::Vec2& position,const int& GID) :
	TileNode(position, TileType::Grass, GID) {

}

// Grass��Ľ�������
void Grass::interact(const std::string& toolName) {
	
}

// Soil�ࣺ���캯��
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Soil, SOIL_GID), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}

// Soil�ࣺ���ݵ�ǰ��״̬����GID
void Soil::updateGID() {

	// ������������������GID
	if (isHoed == false) {
		currentGID = SOIL_GID;
		return;
	}

	// �ж��Ƿ�������
	if (crop == nullptr) {
		if (isWatered == true) {
			currentGID = HOED_SOIL_GID;
		}
		else {
			currentGID = WATER_SOIL_GID;
		}
	}
	else {
		currentGID=crop->getCurrentGID();
		CCLOG("%d",currentGID);
	}
}

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
void Soil::plantCrop(std::string seedName) {
	
	// �ж������Ƿ���ֲ
	if (isHoed == false) {
		return;
	}

	// ��������û�������ʱ��
	if (crop == nullptr) {
		if (seedName == "apple") {		// ��ֲƻ��

		}
		else if(seedName=="corn"){		// ��ֲ����

		}
		else if(seedName=="carrot"){	// ��ֲ���ܲ�
			crop = new Carrot(this->getPosition());
		}
	}
}

// Soil�ࣺ
void Soil::interact(const std::string& toolName) {
	
	// �����빤�ߵĽ���
	if (toolName=="hoe") {						// ����ǳ�ͷ����ô���г���
		hoe();
	}
	else if (toolName == "wateringCan") {		// �����ˮ������ô���н�ˮ
		water();
	}
	else if (toolName == "fertilizer") {		// ����Ƿ��ϣ���ô����ʩ��
		fertilize();
	}
	else if (toolName == "seed") {				// ��������ӣ���ô������ֲ
		plantCrop("carrot");
	}
	updateGID();
}

// ��������ʱ��仯�ĸ��º���
void Soil::updateByTime() {
	if (crop == nullptr) {
		return;
	}
	else {
		crop->grow();
		updateGID();
	}
}

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
	waterResource = (waterResource+200)<MAX_WATER_RESOURCE ? waterResource+200:MAX_WATER_RESOURCE;
}

// Water�ࣺ��õ�ǰˮ��Դ
int Water::getCurrentWaterResource() const {
	return waterResource;
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