/****************************************************************
 * File Function: ʵ�ֶ�Ѩ��ͼ��
 * Author:        ��׿��
 ****************************************************************/
#ifndef __CAVEMAP_H__
#define __CAVEMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "SceneMap.h"

// ��Ѩ��ͼ
class CaveMap : public SceneMap {
public:
    // ��ȡ����ʵ��
    static CaveMap* getInstance();

    // ��ʼ����ͼ
    bool init(const std::string& tmxFile) override;

    // ���µ�ͼλ��
    void moveMapByDirection(const cocos2d::Vec2& direction) override;

    // ��ײ��⣺������λ���Ƿ����ϰ���
    bool isCollidable(const cocos2d::Vec2& position) const override;

    // �����������붴Ѩ�Ľ����߼�
    void interactWithMap() override;

    // ��ͼ����ʱ��ĸ���
    void mapUpdateByTime() override;

private:
    // ���캯������������˽�л�
    CaveMap();
    ~CaveMap();

    // ���ÿ�������͸�ֵ����
    CaveMap(const CaveMap&) = delete;
    CaveMap& operator=(const CaveMap&) = delete;

    // ����ʵ��
    static CaveMap* instance;

    // �����洢TMX��ͼ�ĸ�����
    cocos2d::TMXLayer* backgroundLayer;
    cocos2d::TMXLayer* obstacleLayer;
};

#endif
