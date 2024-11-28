#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// <<<<<<< HEAD
	// =======
	//�õ�ͼ������npc
	std::vector<Npc*> npcs;

	void showDialogue(Npc* npc);  // ������ʾ�Ի���ķ���

	bool isCollidingWithTile(const Vec2& position) const;

	// ��ʼ����ͼͼ��
	void initLayers();

	// ��ʼ����Ƭ�ڵ�
	void initTileNodes();

	// ������Ƭ�ڵ�
	std::shared_ptr<TileNode> createTileNode(const std::string& layerName, const cocos2d::Vec2& position);

	// >>>>>>> 75f5d433ca3bd3759a894911816bae485e86db27
	CREATE_FUNC(Farm);

	bool isDialogueVisible = false;

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