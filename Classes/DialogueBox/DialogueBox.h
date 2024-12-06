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

    // ��ʼ������
    bool init(Npc* npc);

    // ��ʾ�Ի���ĳ�ʼ����
    void showInitialDialogue();

    // ��ʾ�Ի�ѡ��
    void showDialogueOptions(EventListenerMouse* lastListener);

    // ���¶Ի�������
    void updateDialogueAfterOptionSelected(int optionIndex);

    // �رնԻ���
    void closeDialogue(EventListenerMouse* lastListener);

    // ��������¼�����
    void initMouseListener();

    // ��ȡ�¸�����
    std::string getNextFestival();

    static bool isDialogueVisible;  // �Ի����Ƿ���ʾ

private:
    Npc* npc;                                           // ��ǰ��֮�Ի��� NPC
    cocos2d::Label* dialogueLabel;                      //�Ի�����
    cocos2d::Label* nameLabel;                          //npc����
    cocos2d::Sprite* dialogueBackground;                //�Ի�����
    cocos2d::Sprite* npcTalkImage;                      //npc����
    std::vector<cocos2d::ui::Button*> optionButtons;    // �洢�Ի�ѡ�ť
    cocos2d::EventListenerMouse* mouseListener;         // ���ڴ������¼�
};

#endif // __DIALOGUE_BOX_H__
