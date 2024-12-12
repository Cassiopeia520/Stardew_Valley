#pragma once
#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:

    static SkillTreeUI* getInstance();

    // ��ʼ��
    virtual bool init();
    // �Ƿ��
    static bool isOpen;

    void openSkill();

private:
    static SkillTreeUI* instance; // ��̬ʵ��
    // ���о���ʵ��
    void setupUI();

    ~SkillTreeUI();

    // �ر�
    void closeCallback(cocos2d::EventListenerMouse* listener);
};
