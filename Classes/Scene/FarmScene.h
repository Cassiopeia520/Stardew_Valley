#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../DateManage/DateManage.h"
#include "../Map/Animal.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init();

	CREATE_FUNC(Farm);

	//�õ�ͼ������npc
	std::vector<Npc*> npcs;

private:

	void closeButtonClicked(Ref* pSender);

	// ��ʼ����������(ʹ�ù��ߺʹ򿪶Ի���)
	void initMouseListener();

	// �洢ũ���еĶ���
	std::vector<Animal*> animals;


};

#endif