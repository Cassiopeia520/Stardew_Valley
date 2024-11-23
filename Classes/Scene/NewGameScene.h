#ifndef __NEW_GAME_SCENE_H__
#define __NEW_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NewGame : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// ʵ�־�̬create()����
	CREATE_FUNC(NewGame);

private:
	// �����û�������ı�
	cocos2d::ui::TextField* nameInput;

	// ��ť�ص�����
	void onOKButtonClicked(cocos2d::Ref* pSender);

	// ������Ļص�����
	void backCallBack(cocos2d::Ref* pSender);
};

#endif