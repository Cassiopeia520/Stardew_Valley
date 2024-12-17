#ifndef __SCENEMAP_H__
#define __SCENEMAP_H__
#include "cocos2d.h"
#include "TileNode.h"

// ���� SceneMap
class SceneMap : public cocos2d::Node {
public:
    // ��ʼ����ͼ
    virtual bool init(const std::string& tmxFile);

    // ���µ�ͼλ��
    virtual void moveMapByDirection(const cocos2d::Vec2& direction);

    // ��ȡ��ͼ��С
    virtual const cocos2d::Size& getMapSize() const;

    // ��ײ��⣺������λ���Ƿ����ϰ���
    virtual bool isCollidable(const cocos2d::Vec2& position) const;

    // �������������ͼ�Ľ����߼�
    virtual void interactWithMap();

    // ��ͼֹͣ�ƶ�
    virtual void stopMoving();

    // ��ȡ��ͼ����Ƭ��ͼ����
    virtual cocos2d::TMXTiledMap* getTiledMap();

    // ��ȡ��ǰλ�õ�ͼ����
    virtual TileNode* getTileNode(const int x, const int y) const;

    // ��ͼ����ʱ��ĸ���
    virtual void mapUpdateByTime();

protected:
    // ��ͼ��ƫ���ٶ�
    cocos2d::Vec2 velocity;

    // ��Ƭ��ͼ����
    cocos2d::TMXTiledMap* tiledMap;

    // �洢��ͼ��ÿ���ڵ����
    std::vector<std::vector<TileNode*>> mapTileNode;

    // �����洢TMX��ͼ�ĸ�����
    std::vector<cocos2d::TMXLayer*> layers;

    // ͨ�õ�ͼ���غ���
    bool loadMap(const std::string& tmxFile);

    // ���캯������������
    SceneMap();
    virtual ~SceneMap();
};
#endif
