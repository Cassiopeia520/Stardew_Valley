/****************************************************************
 * File Function: ʵ���¿�ʼ��Ϸ�����࣬�̳���Scene���ӿ�ʼ�������л�
 *				  ����������������Լ�����Ϸid
 * Author:        ��׿��
 ****************************************************************/
#ifndef __NEW_GAME_SCENE_H__
#define __NEW_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NewGame : public cocos2d::Scene {
public:
	// ��̬������������
	static cocos2d::Scene* createScene();

private:
	// �����û�������ı�
	cocos2d::ui::TextField* nameInput;

	// ��ť�ص�����
	void onOKButtonClicked(cocos2d::Ref* pSender);

	// ������Ļص�����
	void backCallBack(cocos2d::Ref* pSender);

	// ��ʼ��
	bool init();

	// ʵ�־�̬create()����
	CREATE_FUNC(NewGame);
};

#endif