#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ��ȡ��ҵ���λ�ã����µ�ͼƫ����
	void updateMapPosition();
};

#endif