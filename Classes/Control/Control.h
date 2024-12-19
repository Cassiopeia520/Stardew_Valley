#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../Npc/Npc.h"
#include "../Scene/FarmScene.h"
#include "../DialogueBox/DialogueBox.h"
#include "../Map/SceneMap.h"
#include <set>

// �����࣬ ����������ƶ�����ͼ���ƶ��������npc�Ľ���
// �����಻�ǵ�����ԭ���ж����ͼ��ÿһ����ͼ��Ӧһ��������
class Control : public cocos2d::Node {
public:
	// ��̬����Control����
	static Control* create(SceneMap* sceneMap);

	// ��ʼ��
	bool init(SceneMap* sceneMap);

	// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ���
	void updateMovement();

	// ���캯������������
	Control();
	~Control();
private:
	// ��¼��ǰ���µļ�
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// �ܿ��Ƶĵ�ͼ
	SceneMap* sceneMap;

	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ��ʼ����������
	void initMouseListener();
};
#endif
