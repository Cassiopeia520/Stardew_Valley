#ifndef __DATAMANAGE_H__
#define __DATAMANAGE_H__

#include "cocos2d.h"
#include "../Festival/Festival.h"

// ������ö����
enum class Weather {
    Sunny,
    LightRain,
    HeavyRain,
    Snowy,
};

class DateManage : public cocos2d::Node {
public:
    // ������ʾ���ڵı�ǩ
    cocos2d::Label* dateLabel;

    // ������ʾ��Ǯ�ı�ǩ
    cocos2d::Label* moneyLabel;

    // ���ڵĽ���
    std::vector<Festival*> festivals;

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

    //��ʼ����
    void checkFestivalEvent();

    static DateManage* instance;  // ����ʵ��

    // ��ȡ���ڵ�����
    int getSeasonIndex(const std::string& season);

    //ʱ������
    void updateDate();

    // ��õ�ǰ������
    Weather getCurrentWeather() const;

    // ����ÿ�������
    void updateCurrentWeather();
private:
    // ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
    DateManage();
    ~DateManage();

    // ��ʼ������
    bool init(const int startYear, const int startDay);

    // �洢���ڡ���ݵ���Ϣ
    int currentDay;
    int currentYear;

    // �洢��ǰ������
    Weather currentWeater;
};

#endif
