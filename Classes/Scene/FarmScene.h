#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Map/TileMap.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init();

	//�õ�ͼ������npc
	std::vector<Npc*> npcs;

	// �洢������������
	std::vector<Festival*> festivals;

	// ��ʾ��ʼ�Ի���
	void showInitialDialogue(Npc* npc);

	// ��ʾ�Ի�ѡ��
	void showDialogueOptions(Npc* npc, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel);

	// ����ѡ���ѡ����¶Ի�����
	 void updateDialogueAfterOptionSelected(Npc* npc, std::vector<ui::Button*> optionButtons, int optionIndex, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel) ;

	// �رնԻ�������жԻ�����
	void closeDialogue(Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel);

	bool isCollidingWithTile(const Vec2& position) const;

	// ��ʼ����ͼͼ��
	void initLayers();

	// ��ʼ����Ƭ�ڵ�
	void initTileNodes();

	// ������Ƭ�ڵ�
	std::shared_ptr<TileNode> createTileNode(const std::string& layerName, const cocos2d::Vec2& position);

	void createFestivals();

	void checkFestivalEvent();

	CREATE_FUNC(Farm);

	bool isDialogueVisible;

	void updateDate();

private:
	// ������ʾ���ڵı�ǩ
	cocos2d::Label* dateLabel; 

	// ��¼��ǰ���µļ�
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	std::vector<ui::Button*> optionButtons;  // �洢�Ի�ѡ�ť

	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ���
	void updateMovement();

	// ��ʼ����������
	void initMouseListener();
};

#endif