#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Npc/Npc.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include <string>
#include <memory>
#include <vector>

// ũ����ͼ��
class FarmMap : public cocos2d::Node {
public:
	// ��ȡ����ʵ��
	static FarmMap* getInstance();

	// ��ʼ����ͼ
	bool init(const std::string& tmxFile);

	//���ͼ����npc
	bool npcInit(const cocos2d::Vec2& position, Npc* npc);

	// ���µ�ͼλ��
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// ��ȡ��ͼ��С
	cocos2d::Size getMapSize() const;

	// ��ײ��⣺������λ���Ƿ����ϰ���
	bool isCollidable(const cocos2d::Vec2& position) const;

	// ������������ũ���Ľ����߼�
	void interactWithFarmMap();

	void stopMoving();

	// ��Ƭ��ͼ����
	cocos2d::TMXTiledMap* map;
	
	//��ȡ��ǰλ�õ�ͼ����
	TileNode* getTileNode(int x, int y);

private:

	// ���캯������������˽�л�
	FarmMap();
	~FarmMap();

	// ���ÿ�������͸�ֵ����
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// ��ͼ��ǰ��ƫ��λ��
	cocos2d::Vec2 currentPosition;

	// ��ͼ��ƫ���ٶ�
	cocos2d::Vec2 velocity;

	// ����ʵ��
	static FarmMap* instance;

	// �洢��ͼ��ÿ���ڵ����
	TileNode* mapTileNode[31][17];

	// �����洢TMX��ͼ�ĸ�����
	cocos2d::TMXLayer* grassLayer;
	cocos2d::TMXLayer* soilLayer;
	cocos2d::TMXLayer* obstacleLayer;
	cocos2d::TMXLayer* moldLayer;
	cocos2d::TMXLayer* waterLayer;
	cocos2d::TMXLayer* stoneLayer;
};

#endif