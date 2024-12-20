/****************************************************************
 * File Function: �Ի����࣬����ʵ��Player��Npc��noticeBoard�ĶԻ��Լ�����
 * Author:        Τ���
 ****************************************************************/
#ifndef __DIALOGUE_BOX_H__
#define __DIALOGUE_BOX_H__

#include "cocos2d.h"
#include "../Npc/Npc.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"

class DialogueBox : public cocos2d::Node {
public:
    // ��̬��������
    static DialogueBox* create(Npc* npc);

    //board
    static DialogueBox* create();

    // ��ʼ������
    bool init(Npc* npc);
    //board
    bool init();

    // ��ʾ�Ի���ĳ�ʼ����
    void showInitialDialogue();

    //board
    void showBoardDialogue();

    // ��ʾ�Ի�ѡ��
    void showDialogueOptions(EventListenerMouse* lastListener);

    // ���¶Ի�������
    void updateDialogueAfterOptionSelected(int optionIndex);

    // ������
    void giftBox(std::string giftName, EventListenerKeyboard* lastListener);

    // �رնԻ���
    void closeDialogue(EventListenerMouse* lastListener);

    // ��ȡ�¸�����
    std::string getNextFestival();

    // �Ի���get��set
    static bool getDialogueVisible() { return isDialogueVisible; }
    static void setDialogueVisible(bool status) { isDialogueVisible = status; }

private:
    Npc* npc;                                           // ��ǰ��֮�Ի��� NPC
    cocos2d::Label* dialogueLabel;                      //�Ի�����
    cocos2d::Label* nameLabel;                          //npc����
    cocos2d::Sprite* dialogueBackground;                //�Ի�����
    cocos2d::Sprite* npcTalkImage;                      //npc����
    std::vector<cocos2d::ui::Button*> optionButtons;    // �洢�Ի�ѡ�ť
    cocos2d::EventListenerMouse* mouseListener;         // ���ڴ������¼�
    static bool isDialogueVisible;  // �Ի����Ƿ���ʾ
};

#endif // __DIALOGUE_BOX_H__
