#ifndef __BEACHMAP_H__
#define __BEACHMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"


// ��̲��ͼ
class BeachMap : public cocos2d::Node {
public:
	// ��ȡ����ʵ��
	static BeachMap* getInstance();

	// ��ʼ����ͼ
	bool init(const std::string& tmxFile);

	// ���µ�ͼλ��
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// ��ȡ��ͼ��С
	const cocos2d::Size& getMapSize() const;

	// ��ײ��⣺������λ���Ƿ����ϰ���
	bool isCollidable(const cocos2d::Vec2& position) const;

	// �����������뺣̲�Ľ����߼�
	void interactWithBeachMap();

	// ��ͼֹͣ�ƶ�
	void stopMoving();

	// ��ȡ��ͼ����Ƭ��ͼ����
	cocos2d::TMXTiledMap* getTiledMap();

	//��ȡ��ǰλ�õ�ͼ����
	TileNode* getTileNode(const int x, const int y) const;

	// ��ͼ����ʱ��ĸ���
	void beachMapUpdateByTime();

private:
	// ���캯������������˽�л�
	BeachMap();
	~BeachMap();

	// ���ÿ�������͸�ֵ����
	BeachMap(const BeachMap&) = delete;
	BeachMap& operator=(const BeachMap&) = delete;

	// ��ͼ��ƫ���ٶ�
	cocos2d::Vec2 velocity;

	// ����ʵ��
	static BeachMap* instance;

	// ��Ƭ��ͼ����
	cocos2d::TMXTiledMap* tiledMap;

	// �洢��ͼ��ÿ���ڵ����
	TileNode* mapTileNode[BEACHMAP_WIDTH][BEACHMAP_HEIGHT];

	// �����洢TMX��ͼ�ĸ�����
	cocos2d::TMXLayer* backgroundLayer;
	cocos2d::TMXLayer* waterLayer;
};
#endif
