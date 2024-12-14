#pragma once
#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:
    // ��ȡ����ʵ��
    static SkillTreeUI* getInstance();

    // ��ʼ��
    virtual bool init();

    // �Ƿ��
    static bool isOpen;

    // ��UI����
    void openSkillUI();

private:
    // ��̬ʵ��
    static SkillTreeUI* instance;

    // ���о���ʵ��
    void setupUI();

    // ����������instance������Ұָ��
    ~SkillTreeUI();

    // �رհ�ť�Ļص�����
    void closeCallback(cocos2d::EventListenerMouse* listener);
};
