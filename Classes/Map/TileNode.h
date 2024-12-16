#ifndef __TILE_NODE_H__
#define __TIEL_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Constant/Constant.h"
#include "string"

// ���ļ�����Ƭ��ͼ�Ľڵ�
enum class TileType {
	Grass,
	Soil,
	Obstacle,
	Mold,
	Water,
	Stone,
};

// ��Ƭ��ͼ�ڵ����
class TileNode {
private:
	// �洢�����λ��
	cocos2d::Vec2 position;

	// �洢�ýڵ������
	TileType tileType;

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

	// ��Ƭ��ʱ����º���
	virtual void gidUpdateByTime() {};

	// ��Ƭ��ʱ����º���
	virtual void gidUpdateByEvent() {};
};

// Grass���ʾ�ݣ���TileNode��̳ж���
class Grass : public TileNode {
public:

	// Grass��Ĺ��캯��
	Grass::Grass(const cocos2d::Vec2& position,const int& GID);
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
	// �����Ľ�ˮ
	void water();

	// �����ĳ���
	void hoe();

	// ��������ֲ
	void plantCrop(const std::string& seedName);

	// ������Ĺ��캯��
	Soil(const cocos2d::Vec2& position);

	// ����ʱ����º���
	void gidUpdateByTime() override;

	// �����¼����º���
	void gidUpdateByEvent() override;

	// ������ʩ��
	void fertilize();

	// ����������ջ�
	void harvest();

	// ����״̬�������Ӱ��
	void influenceCropStatus();
};

// Water���ʾˮ����TileNode��̳ж���
class Water : public TileNode {
private:
	// ��ʾ��ǰˮ���е�ˮ��Դ,���е�ˮ��Դ������һ��waterResource
	static int waterResource;
public:

	// ���캯��
	Water(const cocos2d::Vec2& position);

	// �ж�ˮ��Դ�Ƿ�ݽ�
	bool isWaterDepleted() const;

	// ȡˮ
	void pumpWater(int water);

	// ���겹��ˮ��Դ
	void rechargeWaterResource();

	// ��õ�ǰˮ��Դ
	int getCurrentWaterResource() const;

	// Water����ʱ��仯����
	void gidUpdateByTime() override;

	// Water�����¼��仯
	void gidUpdateByEvent() override;
};

// Obstacle�ࣺ�ϰ�
class Obstacle : public TileNode {
public:
	// ���캯��
	Obstacle(const cocos2d::Vec2& position);
};

// STONE���ʾ�ϰ�����TileNode��̳ж���
class Stone : public TileNode {
private:
	int stoneSolidity;		// ʯͷ�ļ�̶̳�
public:
	// ���캯��
	Stone(const cocos2d::Vec2& position);

	// �û�ʯͷ
	void knockRock();

	// �Ƿ񱻻���
	bool isBroken() const;
};

/* Mold�����ڿ����̵�
*/
class Mold : public TileNode {
public:
	Mold(const cocos2d::Vec2& position);
};

#endif