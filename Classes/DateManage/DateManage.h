#ifndef __DATAMANAGE_H__
#define __DATAMANAGE_H__

#include "cocos2d.h"
#include "../Festival/Festival.h"
#include "../Map/FarmMap.h"

class DateManage {
public:
    // ��ȡ����ʵ��
    static DateManage* getInstance();

    // ?? ����ʵ��Ϊʲô����create()�������ο�Player.h // check ��ɾ��

    // ��ȡ��ǰ����
    std::string getCurrentDate() const;
    std::string getCurrentSeason() const;
    int getCurrentDay() const;
    int getCurrentWeekday() const;
    int getCurrentYear() const;

    // �����ƽ�
    void advanceDay();

    // �ж��Ƿ��ǽ���
    bool isFestivalDay() const;

    std::string getNextFestival();

    static DateManage* instance;  // ����ʵ��

    int getSeasonIndex(const std::string& season);

private:
    // ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
    DateManage();
    ~DateManage(); // ��������

    // ��ʼ������
    bool init(int startYear, int startDay);

    // �洢���ڡ���ݵ���Ϣ
    int currentDay;
    int currentYear;

    static const int daysInSeason = 28;  // ÿ�����ڵ�����
    static const int daysInYear = 112;  // ÿ���������4�����ڣ�ÿ��28�죩
    static const int daysInWeek = 7;  // һ��7��
};

#endif
