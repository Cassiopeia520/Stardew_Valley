#include "DateManage.h"

// ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
DateManage::DateManage() : currentYear(0), currentDay(0) {
    // ��ʼ��
}

DateManage* DateManage::instance = nullptr;  // ���岢��ʼ��Ϊ nullptr

DateManage::~DateManage() {
    // ������Դ������еĻ���
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
bool DateManage::init(int startYear, int startDay) {
    currentYear = startYear;
    currentDay = startDay;
    return true;
}

std::string DateManage::getCurrentDate() const {
    int dayOfYear = currentDay % daysInYear;
    int dayInSeason = dayOfYear % daysInSeason + 1; // ��ǰ���ڵĵڼ���
    int seasonIndex = dayOfYear / daysInSeason;
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };

    std::stringstream dateStream;
    dateStream << seasonNames[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

std::string DateManage::getCurrentSeason() const {
    int seasonIndex = (currentDay / daysInSeason) % 4;
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };
    return seasonNames[seasonIndex];
}

int DateManage::getCurrentDay() const {
    return currentDay % daysInSeason + 1; // ��ǰ���ڵĵڼ���
}

int DateManage::getCurrentWeekday() const {
    return currentDay % daysInWeek; // ÿ�ܵ���һ��
}

int DateManage::getDay() const{
    return currentDay;
}

void DateManage::advanceDay() {
    currentDay++;
    if (currentDay >= daysInYear) {
        currentDay = 0; // �µ�һ��
        currentYear++;
    }
}

bool DateManage::isFestivalDay() const {
    // ���ճ�����ÿ�����ڵ��ض�����
    int dayInSeason = getCurrentDay();
    if ((getCurrentSeason() == "Spring" && dayInSeason == 7) ||
        (getCurrentSeason() == "Summer" && dayInSeason == 15) ||
        (getCurrentSeason() == "Fall" && dayInSeason == 5) ||
        (getCurrentSeason() == "Winter" && dayInSeason == 25)) {
        return true;
    }
    return false;
}

int DateManage::getSeasonIndex(const std::string& season) {
    // ӳ�伾���ַ���������
    static std::map<std::string, int> seasonMap = {
        {"Spring", 0},
        {"Summer", 1},
        {"Fall", 2},
        {"Winter", 3}
    };

    // ���Ҳ����ؼ��ڵ�����
    auto it = seasonMap.find(season);
    if (it != seasonMap.end()) {
        return it->second;
    }
    return -1; // ���������Ч������ -1
}
int DateManage::getCurrentYear() const {
    return currentYear;
}
