#include "DateManage.h"
#include "../Constant/Constant.h"

DateManage* DateManage::instance = nullptr;  // ���岢��ʼ��Ϊ nullptr

// ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
DateManage::DateManage()  {}

DateManage::~DateManage() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}

// ��ȡ����ʵ��
DateManage* DateManage::getInstance() {
    if (instance == nullptr) {
        instance = new DateManage();  // ���ʵ�������ڣ�����һ���µ�ʵ��
        instance->init(1, 1);  // Ĭ�ϳ�ʼ�����Ϊ1������Ϊ�� 1 ��
    }

    return instance;
}

// ��ʼ������
bool DateManage::init(const int startYear, const int startDay) {
    currentYear = startYear;
    currentDay = startDay;

    return true;
}

std::string DateManage::getCurrentDate() const {
    int dayInSeason = (currentDay - 1) % DAYSINSEASON + 1; // ��ǰ���ڵĵڼ���
    int seasonIndex = (currentDay - 1) / DAYSINSEASON % 4; // ��������

    std::stringstream dateStream;
    dateStream << SEASONNAME[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

std::string DateManage::getCurrentSeason() const {
    int seasonIndex = ((currentDay - 1) / DAYSINSEASON) % 4;
    return SEASONNAME[seasonIndex];
}

int DateManage::getCurrentDayInSeason() const {
    return (currentDay - 1) % DAYSINSEASON + 1; // ��ǰ���ڵĵڼ���
}

int DateManage::getCurrentDayInWeek() const {
    return (currentDay - 1) % DAYSINWEEK + 1; // ÿ�ܵ���һ��
}

int DateManage::getDay() const{
    return currentDay;
}

void DateManage::advanceDay() {
    ++currentDay;
    if (currentDay > DAYSINYEAR) {
        currentDay = 1; // �µ�һ��
        ++currentYear;
    }
}

bool DateManage::isFestivalDay() const {
    // ���ճ�����ÿ�����ڵ��ض�����
    int dayInSeason = getCurrentDayInSeason();
    if ((getCurrentSeason() == "Spring" && dayInSeason == 7) ||
        (getCurrentSeason() == "Summer" && dayInSeason == 15) ||
        (getCurrentSeason() == "Fall" && dayInSeason == 5) ||
        (getCurrentSeason() == "Winter" && dayInSeason == 25)) {
        return true;
    }
    return false;
}

int DateManage::getSeasonIndex(const std::string& season) {
    auto it = SEASONINDEX.find(season);
        if (it != SEASONINDEX.end()) {
            return it->second;
        }
        else {
            return -1;
        }
}
int DateManage::getCurrentYear() const {
    return currentYear;
}
