/****************************************************************
 * File Function: ʵ�ֺ�̲��ͼ��
 * Author:        ��׿��
 ****************************************************************/
#ifndef __BEACHMAP_H__
#define __BEACHMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "SceneMap.h"


// ��̲��ͼ
class BeachMap : public SceneMap {
public:
	// ��ȡ����ʵ��
	static BeachMap* getInstance();

	// ��ʼ����ͼ
	bool init(const std::string& tmxFile) override;

	// ���µ�ͼλ��
	void moveMapByDirection(const cocos2d::Vec2& direction) override;

	// ��ײ��⣺������λ���Ƿ����ϰ���
	bool isCollidable(const cocos2d::Vec2& position) const override;

	// �����������뺣̲�Ľ����߼�
	void interactWithMap() override;

	// ��ͼ����ʱ��ĸ���
	void mapUpdateByTime() override;

private:
	// ���캯������������˽�л�
	BeachMap();
	~BeachMap();

	// ���ÿ�������͸�ֵ����
	BeachMap(const BeachMap&) = delete;
	BeachMap& operator=(const BeachMap&) = delete;

	// ����ʵ��
	static BeachMap* instance;

	// �����洢TMX��ͼ�ĸ�����
	cocos2d::TMXLayer* backgroundLayer;
	cocos2d::TMXLayer* waterLayer;
};
#endif
