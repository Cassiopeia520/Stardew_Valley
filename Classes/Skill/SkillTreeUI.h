#pragma once
#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:

    static SkillTreeUI* getInstance();

    // ��ʼ��
    virtual bool init();
    // �Ƿ��
    static bool isOpen;

private:
    static SkillTreeUI* instance; // ��̬ʵ��
    // ���о���ʵ��
    void setupUI();
    // �ر�
    void closeCallback(cocos2d::Ref* sender);
};
