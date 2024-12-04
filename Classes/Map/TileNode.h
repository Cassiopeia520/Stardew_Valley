#ifndef __TILE_NODE_H__
#define __TIEL_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "string"

// ���ļ�����Ƭ��ͼ�Ľڵ�
enum class TileType {
	GRASS,
	SOIL,
	OBSTACLE,
	MOLD,
	WATER,
	STONE,
};

// ��Ƭ��ͼ�ڵ����
class TileNode {
private:
	// �洢�����λ��
	cocos2d::Vec2 position;

	// �洢�ýڵ������
	TileType tileType;

	// ��ǰ����ߵ��GID
	int currentGID;

protected:
	// ���µ�ǰ�ڵ��GID
	void updateGID(int newGID) {
		currentGID = newGID;
	}

public:
	// ��Ƭ��ͼ�ڵ����Ĺ��캯��
	TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID);

	// ��ȡ�ýڵ������
	TileType getTileType() const{
		return tileType;
	}

	// ���ظ��������GID
	int getCurrentGID() const {
		return currentGID;
	}

	// TileNode�ڵ�������Ľ���
	virtual void interact(std::string toolName) {};
};

// Grass���ʾ�ݣ���TileNode��̳ж���
class Grass : public TileNode {
public:

	// Grass��Ĺ��캯��
	Grass::Grass(const cocos2d::Vec2& position);

	// �ݵص���ֳ����������ʵ��
	void interact(std::string toolName) override;
};

// Soil���ʾ��������TileNode��̳ж���
class Soil : public TileNode {
private:
	// ��ʾ�����е�����
	Crop* crop;

	// �Ƿ񱻳���
	bool isHoed;

	// �Ƿ��Ѿ���ˮ
	bool isWatered;

	// �Ƿ��Ѿ�ʩ��
	bool isFertilized;

	// �����ĺ�ˮ��
	int waterLevel;

	// �����ĺ�����
	int fertilizeLevel;

	// �����ĳ���
	void hoe();

	// �����Ľ�ˮ
	void water();

	// ������ʩ��
	void fertilize();

	// ��������ֲ
	void plantCrop(std::string seedName);

public:
	// ������Ĺ��캯��
	Soil(const cocos2d::Vec2& position);


	//	�����Ľ�������
	void interact(std::string toolName) override;
};

// Water���ʾˮ����TileNode��̳ж���
class Water : public TileNode {
public:
	Water(const cocos2d::Vec2& position) :
		TileNode(position, TileType::WATER,17)
	{}
};

// Obstacle���ʾ�ϰ�����TileNode��̳ж���
class Obstacle : public TileNode {
public:
	Obstacle(const cocos2d::Vec2& position) :
		TileNode(position,TileType::OBSTACLE,100)
	{}
};

// MOLD���ʾ���ӣ���TileNode��̳ж���
class Mold : public TileNode {
public:
	Mold(const cocos2d::Vec2& position) :
		TileNode(position, TileType::MOLD,200)
	{}
};

// STONE���ʾ�ϰ�����TileNode��̳ж���
class Stone : public TileNode {
public:
	Stone(const cocos2d::Vec2& position) :
		TileNode(position, TileType::STONE,22)
	{}
};

#endif