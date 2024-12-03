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
	TileNode(const cocos2d::Vec2& position, const TileType& tileType,const int& currentGID) :
		position(position), tileType(tileType),currentGID(currentGID)
	{} // ?? ע�����ŵĸ�ʽ���ֺ������ļ�ͳһ�����ﲻӦ������һ�С�����������.h�ļ������ڷǾ�̬��Ա�����ͺ���ֻӦ����������Ӧ���ж���

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
	Grass(const cocos2d::Vec2& position):
		TileNode(position,TileType::GRASS,1)
	{}

	// �ݵص���ֳ����������ʵ��
	virtual void interact(std::string toolName);
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
public:
	// ������Ĺ��캯��
	Soil(const cocos2d::Vec2& position) :
		TileNode(position, TileType::SOIL,3), crop(nullptr),
		isWatered(false), isFertilized(false), isHoed(false),
		waterLevel(0),fertilizeLevel(0)
	{}

	// �����ĳ���
	void hoe();

	// �����Ľ�ˮ
	void water();

	// ������ʩ��
	void fertilize();

	// ?? ���Ҳд�麯������ΪSoil������������
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