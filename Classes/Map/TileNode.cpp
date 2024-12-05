#include "TileNode.h"


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
	TileNode(position, TileType::GRASS, GID) {

}

// Grass��Ľ�������
void Grass::interact(const std::string& toolName) {
	
}

// Soil�ࣺ���캯��
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::SOIL, HOED_SOIL_GID), crop(nullptr),
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
	this->updateGID();
}

// Water�ࣺ���캯��
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::WATER, WATER_GID){}

// Water�ࣺ��������
void Water::interact(const std::string& toolName) {

}

// Stone�ࣺ���캯��
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::STONE, STONE_GID) {}