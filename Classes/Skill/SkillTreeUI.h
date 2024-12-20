/****************************************************************
 * File Function: �������ڳ�����չʾ�࣬����ʵ�ּ���������ʾ�����
 * Author:        Τ���
 ****************************************************************/
#ifndef __SKILLTREEUI_H__
#define __SKILLTREEUI_H__

#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:
    // ��ȡ����ʵ��
    static SkillTreeUI* getInstance();

    // ��ʼ��
    virtual bool init();

    // ��UI����
    void openSkillUI();

    // �Ƿ��
    static bool getOpenStatus() { return isOpen; }

    // open״̬����
    static void setOpenStatus(bool status) { isOpen = status; }

    //������ʾ״̬
    void updateUI();

private:
    // ��̬ʵ��
    static SkillTreeUI* instance;

    // ���о���ʵ��
    void setupUI();

    // ����������instance������Ұָ��
    ~SkillTreeUI();

    // �رհ�ť�Ļص�����
    void closeCallback(cocos2d::EventListenerMouse* listener);

    // �Ƿ��
    static bool isOpen;
};
#endif __SKILLTREEUI_H__