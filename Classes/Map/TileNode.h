#ifndef __TILE_NODE_H__
#define __TILE_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Constant/Constant.h"
#include "string"

/*
 * Class Name:     TileType
 * Class Function: �ߵ�����
 */
enum class TileType {
	Grass,
	Soil,
	Obstacle,
	Mold,
	Water,
	Stone,
};

/*
 * Class Name:     TileNode
 * Class Function: �ߵ����
 */
class TileNode {
private:
	// �ߵ�λ��
	cocos2d::Vec2 position;

	// �ߵ�����
	TileType tileType;
	
protected:
	// �ߵ��GID
	int currentGID;

public:
	// ���캯��
	TileNode(const cocos2d::Vec2& position, const TileType& tileType);

	// ��ʼ��
	virtual bool init();

	// �����ߵ������
	TileType getTileType() const;

	// �����ߵ�GID
	int getCurrentGID() const;

	// �����ߵ�λ��
	cocos2d::Vec2 getNodePosition() const;

	// �����ߵ�GID
	virtual void updateGID();
};

/*
 * Class Name:	   Grass
 * Class Function: ��ͼ�еĲ�
 */
class Grass : public TileNode {
public:
	// ��̬��������
	static Grass* create(const cocos2d::Vec2& position);

	// ���캯��
	Grass::Grass(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;
};

/*
 * Class Name:	   Soil
 * Class Function: ��ͼ�е�����
 */
class Soil : public TileNode {
private:
	// ����
	Crop* crop;

	// �Ƿ񱻳���
	bool isHoed;

	// ��ˮ��
	int waterLevel;

	// ������
	int fertilizeLevel;

	// �����GID�ж�
	int judgeDogbaneGID(int growStage);

	// ����GID�ж�
	int judgeCornGID(int growStage);

	// ���ܲ�GID�ж�
	int judgeCarrotGID(int growStage);

public:
	// ��̬��������
	static Soil* create(const cocos2d::Vec2& position);

	// ���캯��
	Soil(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;

	// ����
	void soilHoe();

	// ��ˮ
	void soilWater();

	// ʩ��
	void soilFertilize();

	// ��ֲ����
	void plantCrop(std::string seedName);

	// �ж��Ƿ�������
	bool isPlanted() const;

	// ��������
	void cropGrow();

	// Ӧ��ũҩ
	void applyAgrochemical();

	// �ջ�����
	void harvest();

	// ��ʱ��仯
	void updateByTime();

	// ����ͼ��
	void updateGID() override;
};


class Water : public TileNode {
public:
	// ��̬��������
	static Water* create(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;

	// ���캯��
	Water(const cocos2d::Vec2& position);
};

class Obstacle : public TileNode {
public:
	// ��̬��������
	static Obstacle* create(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;

	// ���캯��
	Obstacle(const cocos2d::Vec2& position);
};

class Stone : public TileNode {
private:
	// ��̶̳�
	int stoneSolidity;		
public:
	// ��̬��������
	static Stone* create(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;

	// ���캯��
	Stone(const cocos2d::Vec2& position);

	// �û�ʯͷ
	void knockRock();

	// �Ƿ񱻻���
	bool isBroken() const;
};


class Mold : public TileNode {
public:
	// ��̬��������
	static Mold* create(const cocos2d::Vec2& position);

	// ��ʼ��
	bool init() override;

	Mold(const cocos2d::Vec2& position);
};

#endif