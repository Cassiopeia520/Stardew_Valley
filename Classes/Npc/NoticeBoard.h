#ifndef __NOTICE_BOARD_H__
#define __NOTICE_BOARD_H__

#include <string>
#include "cocos2d.h"
#include "../Constant/Constant.h"

USING_NS_CC;

class NoticeBoard : public Sprite{
public:

    static NoticeBoard* create();

    bool init(const ItemInfo& noticeBoardInfo);

    // �Ի���Ϣ
    std::string printDialogue() const;

    //�������
    static bool getTaskStatus() { return isTaskCompleted; }
    bool completeTask() { return isTaskCompleted = true; }

    //bool boardAdd() { return isAdded = true; }
    //bool isBoardAdded() const { return isAdded; }

private:
    std::string name;
    std::string image;
    static bool isTaskCompleted;
    //static bool isAdded;
};

#endif // __NOTICE_BOARD_H__
