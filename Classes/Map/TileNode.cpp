#include "TileNode.h"
#include<iostream>




// TileNode���ࣺ���캯��
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID) :
	position(position), tileType(tileType), currentGID(currentGID) {

}

// Grass�ࣺ���캯��
Grass::Grass(const cocos2d::Vec2& position) :
	TileNode(position, TileType::GRASS, 5) {

}

// Grass��Ľ�������
void Grass::interact(std::string toolName) {
	// �ж϶���
	if (toolName == "crow") {				// ţ

	}
	else if (toolName == "chicken") {		// ��

	}
	else if (toolName == "sheep") {			// ��

	}
	else if (toolName == "pig") {			// ��

	}
}

// Soil�ࣺ���캯��
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::SOIL, 36), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}


// Soil�ࣺ����
void Soil::hoe() {
	isHoed = true;
	this->updateGID(64);
}

// Soil�ࣺ��ˮ
void Soil::water() {
	if (isHoed ) {
		// �ж��������λ���Ƿ�������
		if (crop == nullptr) {
			this->updateGID(96);
		}
		// ����������״̬
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
	// ��������û�������ʱ��
	if (crop == nullptr) {
		if (seedName == "apple") {		// ��ֲƻ��

		}
		else if(seedName=="corn"){		// ��ֲ����

		}
		else if(seedName=="carrot"){	// ��ֲ���ܲ�
			
		}
	}
}

// Soil�ࣺ
void Soil::interact(std::string toolName) {
	
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

	}
}