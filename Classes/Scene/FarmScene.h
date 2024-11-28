#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"
#include "../Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// ��¼��ǰ���µļ�
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ���
	void updateMovement();

	// ��ʼ����������
	void initMouseListener();
};

#endif