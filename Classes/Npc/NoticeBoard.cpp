/****************************************************************
 * File Function: ʵ�ָ�ʾ���࣬�̳�Sprite�࣬������ʾ������ض�npc����������
 * Author:        Τ���
 ****************************************************************/
#include "NoticeBoard.h"

USING_NS_CC;

bool NoticeBoard::isTaskCompleted = false;

// ��������
NoticeBoard* NoticeBoard::create() {
    NoticeBoard* noticeBoard = new (std::nothrow) NoticeBoard;
    if (noticeBoard && noticeBoard->init(BOARD)) {
        noticeBoard->autorelease();
        return noticeBoard;
    }
    CC_SAFE_DELETE(noticeBoard);
    return nullptr;
}

//init����
bool NoticeBoard::init(const ItemInfo& noticeBoardInfo) {
    if (!Sprite::initWithFile(noticeBoardInfo.image)) {
        return false;
    }
    name = noticeBoardInfo.name;
    image = noticeBoardInfo.image;
    return true;
}

//���ع̶��ĶԻ�����
std::string NoticeBoard::printDialogue() const {
    if (!isTaskCompleted)
        return "It's levi's unique task.Find 3 pieces of  stones to build it up.";
    return "...";
}
