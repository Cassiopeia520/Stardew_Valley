/****************************************************************
 * File Function: ʵ�������¼��࣬������࣬���������¼�
 * Author:        Τ���
 ****************************************************************/
#include "CommunityEvent.h"

// ��ʼ��
bool CommunityEvent::init(const std::string& name, const std::string& description, const std::string& date) {
    // ��ʼ������
    eventName = name;
    eventDescription = description;
    eventDate = date;
    return true;  // �����ʼ���ɹ�
}

// ��ʼ�¼�
void CommunityEvent::startEvent() {

}

// ��ȡ�¼�����
std::string CommunityEvent::getEventName() const {
    return eventName;
}

// ��ȡ�¼�����
std::string CommunityEvent::getEventDescription() const {
    return eventDescription;
}

// ��ȡ�¼�����
std::string CommunityEvent::getEventDate() const {
    return eventDate;
}
