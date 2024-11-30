#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "../CommunityEvent/CommunityEvent.h"
#include "../DateManage/DateManage.h"

class Festival : public CommunityEvent {
public:
    static Festival* create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // ��ʼ������
    bool init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    void startEvent(DateManage* dateManager);  // ��д�¼���ʼ�߼�

    bool isHoliday() const;

protected:
    bool holiday;  // �Ƿ�Ϊ�ڼ���

    Festival();
};

#endif // __FESTIVAL_H__
