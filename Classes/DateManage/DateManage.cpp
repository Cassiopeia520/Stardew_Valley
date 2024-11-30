#include "DateManage.h"

// ��ʼ������ʵ��ָ��
DateManage* DateManage::instance = nullptr;

// ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
DateManage::DateManage() : currentYear(0), currentDay(0) {
    // ��ʼ��
}

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

// �����µ� DateManage ʵ������ָ����ʼ��ݺ�����
DateManage* DateManage::create(int startYear, int startDay) {
    DateManage* instance = new DateManage();
    if (instance && instance->init(startYear, startDay)) {
        return instance;  // �����ʼ���ɹ����򷵻�ʵ��
    }
    delete instance;  // ����ɾ��ʵ��
    return nullptr;
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

void DateManage::advanceDay() {
    currentDay++;
    if (currentDay >= daysInYear) {
        currentDay = 0; // �µ�һ��
        currentYear++;
    }
}

bool DateManage::isFestivalDay() const {
    // ���ճ�����ÿ�����ڵ��ض����ڣ�Spring 13, Summer 11, Fall 16, Winter 8
    int dayInSeason = getCurrentDay();
    if ((getCurrentSeason() == "Spring" && dayInSeason == 13) ||
        (getCurrentSeason() == "Summer" && dayInSeason == 11) ||
        (getCurrentSeason() == "Fall" && dayInSeason == 16) ||
        (getCurrentSeason() == "Winter" && dayInSeason == 8)) {
        return true;
    }
    return false;
}

int DateManage::getCurrentYear() const {
    return currentYear;
}
