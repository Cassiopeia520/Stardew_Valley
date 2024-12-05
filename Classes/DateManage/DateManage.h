#ifndef __DATAMANAGE_H__
#define __DATAMANAGE_H__

#include "cocos2d.h"
#include "../Festival/Festival.h"

class DateManage {
public:
    // ��ȡ����ʵ��
    static DateManage* getInstance();

    // ��ȡ��ǰ����
    std::string getCurrentDate() const;
    std::string getCurrentSeason() const;

    // ��ȡ��ǰ���ĵڼ���
    int getCurrentDayInSeason() const;

    // ��ȡ��ǰ�ܵĵڼ���
    int getCurrentDayInWeek() const;

    // ��ȡ��ǰ�����
    int getCurrentYear() const;

    // ��ȡ���ۼ�����
    int getDay() const;

    // �����ƽ�
    void advanceDay();

    // �ж��Ƿ��ǽ���
    bool isFestivalDay() const;

    //std::string getNextFestival();

    static DateManage* instance;  // ����ʵ��

    // ��ȡ���ڵ�����
    int getSeasonIndex(const std::string& season);

private:
    // ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
    DateManage();
    ~DateManage();

    // ��ʼ������
    bool init(const int startYear, const int startDay);

    // �洢���ڡ���ݵ���Ϣ
    int currentDay;
    int currentYear;
};

#endif
