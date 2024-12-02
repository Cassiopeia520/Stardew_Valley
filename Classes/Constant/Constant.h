#ifndef __CONSTANT_H
#define __CONSTANT_H
#include "../Npc/Npc.h"
#include "cocos2d.h"

// ��Դ·��
namespace ResPath {
	constexpr char BACKGROUND_IMAGE[] = "icon/background.png";
	constexpr char NEW_GAME_ITEM[] = "icon/newGameButton.png";
	constexpr char LOAD_GAME_ITEM[] = "icon/loadGameButton.png";
	constexpr char COOPERATION_ITEM[] = "icon/cooperationButton.png";
	constexpr char EXIT_ITEM[] = "icon/exitButton.png";
	constexpr char TITLE[] = "icon/title.png";
	constexpr char FONT_TTF[] = "fonts/Marker Felt.ttf";
}

// WecomScene
constexpr float MENU_ITEM_INTERVAL = 24.0f; // �˵���֮��ļ��
constexpr float WELCOME_LABEL_SIZE = 24.0f; // Weclome��ǩ�����С

constexpr float MAP_MOVE_SPEED = 400.0f; // ��ͼ�ƶ��ٶ�
constexpr float PLAYER_MOVE_SPEED = 200.0f; // ����ƶ��ٶ�

// NPC
constexpr float interactionRange = 100.0f;  // �ɵ�������ֵ����ʾ����� NPC ֮�����󽻻�����
constexpr int WIZARD_X = 300;
constexpr int WIZARD_Y = 300;
constexpr int CLEANER_X = 500;
constexpr int CLEANER_Y = 300;

constexpr int TALKING_BOX_WIDTH = 1283;
constexpr int TALKING_BOX_HEIGHT = 462;

constexpr int TALKING_BOX_X = 640;
constexpr int TALKING_BOX_Y = 200;

constexpr int LABEL_WIDTH = 720;
constexpr int LABEL_HEIGHT = 390;

const cocos2d::Size WINSIZE(1280.0f, 720.0f);

const Npc WIZARD("Wizard Yuuu", "Fall 5",
	{ "Magic Essence", "Diamond" },
	{ "Milk" },
	{ "Get out of my way.", "It's nice to see you here.", "I like to spend time with you." },
	"npcImages/wizard.png");
const Npc CLEANER("Cleaner Levi", "Winter 25",
	{ "Milk", "Cleaning tools" },
	{ "Clay" },
	{ "...", "Ahh, hi.", "Come and have some black-tea with me." },
	"npcImages/cleaner.png");


#endif __CONSTANT_H
