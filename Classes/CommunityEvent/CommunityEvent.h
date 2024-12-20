/****************************************************************
 * File Function: �����¼��࣬������࣬���������¼�
 * Author:        Τ���
 ****************************************************************/
#ifndef __COMMUNITY_EVENT_H__
#define __COMMUNITY_EVENT_H__

#include <string>
#include "cocos2d.h"

class DateManage; // ǰ������ DateManage ��

class CommunityEvent {
public:

    virtual ~CommunityEvent() = default;

    // ���з����������¼�
    virtual void startEvent() = 0;

    // ��ȡ�¼�����
    std::string getEventName() const;

    // ��ȡ�¼�����
    std::string getEventDescription() const;

    // ��ȡ�¼�����
    std::string getEventDate() const;

protected:

    // ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
    CommunityEvent() = default;

    // ˽�г�ʼ������
    bool init(const std::string& name, const std::string& description, const std::string& date);

    // �¼��ĳ�Ա����
    std::string eventName;
    std::string eventDescription;
    std::string eventDate;
};

#endif // __COMMUNITY_EVENT_H__
