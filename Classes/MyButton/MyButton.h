/****************************************************************
 * File Function: ʵ���Զ��尴ť�࣬ʵ��������ť
 * Author:        ��׿��
 ****************************************************************/
#ifndef __HOVERBUTTON_H__
#define __HOVERBUTTON_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>

class MyButton : public cocos2d::ui::Button {
public:
	static MyButton* create(const std::string& normalImage, const std::string& hoverImage);
	bool isHover();

private:
	bool init(const std::string& normalImage, const std::string& hoverImage);

	std::string normal; // ����״̬�°�ťͼƬ·��
	std::string hover;  // �������״̬�°�ťͼƬ·��

	cocos2d::EventListenerMouse* mouseListener;

	// ����ƶ��¼��Ĵ�����
	void onMouseMove(cocos2d::Event* event);

	bool hoverState;
};

#endif
