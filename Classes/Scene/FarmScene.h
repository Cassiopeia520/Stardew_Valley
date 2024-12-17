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

// ũ��������
class Farm : public cocos2d::Scene {
public:
	// ������������̬����
	static cocos2d::Scene* createScene();

	// ������������̬���� create()
	CREATE_FUNC(Farm);

	//�õ�ͼ������npc����̬��Ա����
	static std::vector<Npc*> npcs;

	// ���������λ���Զ���ũ�������л��������ĸ�����
	void changeSceneAuto();

	// ��������������npcs���ڴ����
	~Farm();
private:
	// ũ�������ĳ�ʼ������
	bool init();

	// �رհ�ť�Ļص�����
	void closeButtonClicked(Ref* pSender);
};

#endif