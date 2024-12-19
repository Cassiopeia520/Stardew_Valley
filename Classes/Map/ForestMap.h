#ifndef __FORESTMAP_H__
#define __FORESTMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "SceneMap.h"

// ɭ�ֵ�ͼ
class ForestMap : public SceneMap {
public:
    // ��ȡ����ʵ��
    static ForestMap* getInstance();

    // ��ʼ����ͼ
    bool init(const std::string& tmxFile) override;

    // ���µ�ͼλ��
    void moveMapByDirection(const cocos2d::Vec2& direction) override;

    // ��ײ��⣺������λ���Ƿ����ϰ���
    bool isCollidable(const cocos2d::Vec2& position) const override;

    // ������������ɭ�ֵĽ����߼�
    void interactWithMap() override;

    // ��ͼ����ʱ��ĸ���
    void mapUpdateByTime() override;

private:
    // ���캯������������˽�л�
    ForestMap();
    ~ForestMap();

    // ���ÿ�������͸�ֵ����
    ForestMap(const ForestMap&) = delete;
    ForestMap& operator=(const ForestMap&) = delete;

    // ����ʵ��
    static ForestMap* instance;

    // �����洢TMX��ͼ�ĸ�����
    cocos2d::TMXLayer* backgroundLayer;
};

#endif
