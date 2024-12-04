#ifndef __CONSTANT_H
#define __CONSTANT_H
#include "../Npc/Npc.h"
#include "cocos2d.h"

// 资源路径
namespace ResPath {
	// 背景框、按钮、字体
	constexpr char BACKGROUND_IMAGE[] = "icon/background.png";
	constexpr char NEW_GAME_ITEM[] = "icon/newGameButton.png";
	constexpr char LOAD_GAME_ITEM[] = "icon/loadGameButton.png";
	constexpr char COOPERATION_ITEM[] = "icon/cooperationButton.png";
	constexpr char EXIT_ITEM[] = "icon/exitButton.png";
	constexpr char TITLE[] = "icon/title.png";
	constexpr char FONT_TTF[] = "fonts/Marker Felt.ttf";
	constexpr char COOP_BACKGROUND[] = "icon/coopBackground.png";
	constexpr char COOP_PANEL[] = "icon/cooperationPanel.png";
	constexpr char NAME_BAR[] = "icon/nameBar.png";
	constexpr char OK_BUTTON[] = "icon/okButton.png";
	constexpr char BACK_BUTTON[] = "icon/backButton.png";
	constexpr char UP_ARROW[] = "icon/upArrow.png";
	constexpr char DOWN_ARROW[] = "icon/downArrow.png";

	// Axe 动画帧
	constexpr char AXE_RIGHT_1[] = "tools/axe/rightUseAxe1.png";
	constexpr char AXE_RIGHT_2[] = "tools/axe/rightUseAxe2.png";
	constexpr char AXE_RIGHT_3[] = "tools/axe/rightUseAxe3.png";
	constexpr char AXE_LEFT_1[] = "tools/axe/leftUseAxe1.png";
	constexpr char AXE_LEFT_2[] = "tools/axe/leftUseAxe2.png";
	constexpr char AXE_LEFT_3[] = "tools/axe/leftUseAxe3.png";
	constexpr char AXE_UP_1[] = "tools/axe/upUseAxe1.png";
	constexpr char AXE_UP_2[] = "tools/axe/upUseAxe2.png";
	constexpr char AXE_UP_3[] = "tools/axe/upUseAxe3.png";
	constexpr char AXE_DOWN_1[] = "tools/axe/downUseAxe1.png";
	constexpr char AXE_DOWN_2[] = "tools/axe/downUseAxe2.png";
	constexpr char AXE_DOWN_3[] = "tools/downUseAxe3.png";

	// Hoe 动画帧路径
	constexpr char HOE_RIGHT_1[] = "tools/hoe/rightUseHoe1.png";
	constexpr char HOE_RIGHT_2[] = "tools/hoe/rightUseHoe2.png";
	constexpr char HOE_RIGHT_3[] = "tools/hoe/rightUseHoe3.png";
	constexpr char HOE_LEFT_1[] = "tools/hoe/leftUseHoe1.png";
	constexpr char HOE_LEFT_2[] = "tools/hoe/leftUseHoe2.png";
	constexpr char HOE_LEFT_3[] = "tools/hoe/leftUseHoe3.png";
	constexpr char HOE_UP_1[] = "tools/hoe/upUseHoe1.png";
	constexpr char HOE_UP_2[] = "tools/hoe/upUseHoe2.png";
	constexpr char HOE_UP_3[] = "tools/hoe/upUseHoe3.png";
	constexpr char HOE_DOWN_1[] = "tools/hoe/downUseHoe1.png";
	constexpr char HOE_DOWN_2[] = "tools/hoe/downUseHoe2.png";

	// Pickaxe 动画帧路径
	constexpr char PICKAXE_RIGHT_1[] = "tools/pickaxe/rightUsePickaxe1.png";
	constexpr char PICKAXE_RIGHT_2[] = "tools/pickaxe/rightUsePickaxe2.png";
	constexpr char PICKAXE_RIGHT_3[] = "tools/pickaxe/rightUsePickaxe3.png";
	constexpr char PICKAXE_LEFT_1[] = "tools/pickaxe/leftUsePickaxe1.png";
	constexpr char PICKAXE_LEFT_2[] = "tools/pickaxe/leftUsePickaxe2.png";
	constexpr char PICKAXE_LEFT_3[] = "tools/pickaxe/leftUsePickaxe3.png";
	constexpr char PICKAXE_UP_1[] = "tools/pickaxe/upUsePickaxe1.png";
	constexpr char PICKAXE_UP_2[] = "tools/pickaxe/upUsePickaxe2.png";
	constexpr char PICKAXE_DOWN_1[] = "tools/pickaxe/downUsePickaxe1.png";
	constexpr char PICKAXE_DOWN_2[] = "tools/pickaxe/downUsePickaxe2.png";
	constexpr char PICKAXE_DOWN_3[] = "tools/pickaxe/downUsePickaxe3.png";

	// 玩家站立帧
	constexpr char STAND_RIGHT[] = "playerWalkImages/standRight.png";
	constexpr char STAND_LEFT[] = "playerWalkImages/standLeft.png";
	constexpr char STAND_UP[] = "playerWalkImages/standUp.png";
	constexpr char STAND_DOWN[] = "playerWalkImages/standDown.png";
}

// 工具动画帧的裁剪区域
namespace ToolRects {
	// Axe 动画帧 Rect
	const cocos2d::Rect AXE_RIGHT_1(0, 0, 100, 183);
	const cocos2d::Rect AXE_RIGHT_2(0, 0, 201, 183);
	const cocos2d::Rect AXE_RIGHT_3(0, 0, 165, 164);
	const cocos2d::Rect AXE_LEFT_1(0, 0, 100, 183);
	const cocos2d::Rect AXE_LEFT_2(0, 0, 201, 183);
	const cocos2d::Rect AXE_LEFT_3(0, 0, 165, 164);
	const cocos2d::Rect AXE_UP_1(0, 0, 85, 200);
	const cocos2d::Rect AXE_UP_2(0, 0, 81, 127);
	const cocos2d::Rect AXE_UP_3(0, 0, 75, 145);
	const cocos2d::Rect AXE_DOWN_1(0, 0, 74, 185);
	const cocos2d::Rect AXE_DOWN_2(0, 0, 75, 127);
	const cocos2d::Rect AXE_DOWN_3(0, 0, 77, 109);

	// Hoe 动画帧 Rect
	const cocos2d::Rect HOE_RIGHT_1(0, 0, 128, 180);
	const cocos2d::Rect HOE_RIGHT_2(0, 0, 169, 184);
	const cocos2d::Rect HOE_RIGHT_3(0, 0, 206, 271);
	const cocos2d::Rect HOE_LEFT_1(0, 0, 128, 180);
	const cocos2d::Rect HOE_LEFT_2(0, 0, 169, 184);
	const cocos2d::Rect HOE_LEFT_3(0, 0, 206, 271);
	const cocos2d::Rect HOE_UP_1(0, 0, 89, 190);
	const cocos2d::Rect HOE_UP_2(0, 0, 83, 190);
	const cocos2d::Rect HOE_UP_3(0, 0, 97, 145);
	const cocos2d::Rect HOE_DOWN_1(0, 0, 70, 196);
	const cocos2d::Rect HOE_DOWN_2(0, 0, 70, 195);

	// Pickaxe 动画帧 Rect
	const cocos2d::Rect PICKAXE_RIGHT_1(0, 0, 131, 198);
	const cocos2d::Rect PICKAXE_RIGHT_2(0, 0, 95, 193);
	const cocos2d::Rect PICKAXE_RIGHT_3(0, 0, 267, 183);
	const cocos2d::Rect PICKAXE_LEFT_1(0, 0, 131, 198);
	const cocos2d::Rect PICKAXE_LEFT_2(0, 0, 95, 193);
	const cocos2d::Rect PICKAXE_LEFT_3(0, 0, 267, 183);
	const cocos2d::Rect PICKAXE_UP_1(0, 0, 98, 261);
	const cocos2d::Rect PICKAXE_UP_2(0, 0, 93, 146);
	const cocos2d::Rect PICKAXE_DOWN_1(0, 0, 86, 270);
	const cocos2d::Rect PICKAXE_DOWN_2(0, 0, 81, 203);
	const cocos2d::Rect PICKAXE_DOWN_3(0, 0, 63, 132);

	// 玩家站立帧 Rect
	const cocos2d::Rect STAND_RIGHT(0, 0, 70, 120);
	const cocos2d::Rect STAND_LEFT(0, 0, 70, 120);
	const cocos2d::Rect STAND_UP(0, 0, 70, 120);
	const cocos2d::Rect STAND_DOWN(0, 0, 70, 120);
}

// 全局窗口大小
const cocos2d::Size WINSIZE(1280.0f, 720.0f);

// 全局移动速度
constexpr float MAP_MOVE_SPEED = 400.0f;			// 地图移动速度
constexpr float PLAYER_MOVE_SPEED = 200.0f;			// 玩家移动速度

// WecomScene
constexpr float MENU_ITEM_INTERVAL = 24.0f;			// 菜单项之间的间距
constexpr float WELCOME_LABEL_SIZE = 24.0f;			// Weclome标签字体大小

// NewGameScene
constexpr char DEFAULT_PLAYER_NAME[] = "Kuanye";	// 默认玩家名字
constexpr float OK_BUTTON_POSITION_X_RATIO = 0.7f;	// OK按钮X轴位置比例
constexpr float OK_BUTTON_POSITION_Y_RATIO = 0.3f;	// OK按钮Y轴位置比例
constexpr float BACK_BUTTON_PADDING_RIGHT = 40.0f;	// 返回按钮右边距
constexpr float BACK_BUTTON_PADDING_BOTTOM = 20.0f; // 返回按钮下边距

// CooperationScene
constexpr float ARROW_BUTTON_PADDING = 40.0f;		// 翻页按钮的右边距
constexpr float UP_BUTTON_OFFSET_Y = 50.0f;			// 向上箭头按钮Y轴偏移
constexpr float DOWN_BUTTON_OFFSET_Y = -50.0f;		// 向下箭头按钮Y轴偏移
constexpr float MOVE_BY_DISTANCE = 50.0f;			// 翻页按钮移动的像素距离
constexpr char COOP_TEXT_CONTENT[] = "Connecting to online services...";

// NPC
constexpr float interactionRange = 100.0f;			// 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
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


// Crop
constexpr int WATER_SCARCITY_DAY = 5;
constexpr int INFESTED_DAY = 5;

#endif __CONSTANT_H
