#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../Npc/Npc.h"
#include "../Scene/FarmScene.h"
#include "../DialogueBox/DialogueBox.h"
#include <set>

// �����࣬ ����������ƶ�����ͼ���ƶ��������npc�Ľ���
// �����಻�ǵ�����ԭ�򣺿��ܻ��ж��������ÿһ������һ��������
class Control : public cocos2d::Node {
public:
	// ��̬����Control����
	static Control* create();

	// ��ʼ��
	bool init();

	// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ��򣻾�̬��Ա����������ȫ�ַ���
	static void updateMovement();

private:
	// ��¼��ǰ���µļ�����̬��Ա��������Ϊ��updateMovement()����Ҫ����
	static std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ��ʼ����������
	void initMouseListener();

	
};


#endif
