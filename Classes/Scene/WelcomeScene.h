#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init();
    // ����Ϸ��Ļص�����
    void menuNewGameCallback(cocos2d::Ref* pSender);

    // ������Ϸ��Ļص�����
    void menuLoadGameCallback(cocos2d::Ref* pSender);

    // ������Ļص�����
    void menuCooperationCallback(cocos2d::Ref* pSender);

    // �˳���Ļص�����
    void menuExitCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Welcome);
};
#endif // __WELCOME_SCENE_H__
