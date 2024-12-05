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

	// ���µ�ǰ�ڵ��GID
	virtual void updateGID();

protected:

	// ��ǰ����ߵ��GID
	int currentGID;

public:
	// ��Ƭ��ͼ�ڵ����Ĺ��캯��
	TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID);

	// ��ȡ�ýڵ������
	TileType getTileType() const;

	// ���ظ��������GID
	int getCurrentGID() const;

	// ��ȡ��TileNode�ڵ��λ��
	cocos2d::Vec2 getPosition() const;

	// TileNode�ڵ�������Ľ���
	virtual void interact(const std::string& toolName) {};

};

// Grass���ʾ�ݣ���TileNode��̳ж���
class Grass : public TileNode {
public:

	// Grass��Ĺ��캯��
	Grass::Grass(const cocos2d::Vec2& position,const int& GID);

	// �ݵص���ֳ����������ʵ��
	void interact(const std::string& toolName) override;
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

	// updateGID����д
	void updateGID() override;
public:
	// ������Ĺ��캯��
	Soil(const cocos2d::Vec2& position);

	//	�����Ľ�������
	void interact(const std::string& toolName) override;

};

// Water���ʾˮ����TileNode��̳ж���
class Water : public TileNode {
public:

	// Water���ʾˮ
	Water(const cocos2d::Vec2& position);

	// Water��Ľ�������
	void interact(const std::string& toolName) override;
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
	// ���캯��
	Stone(const cocos2d::Vec2& position);
};

#endif