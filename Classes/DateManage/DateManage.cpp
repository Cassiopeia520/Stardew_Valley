#include "DateManage.h"
#include "../Constant/Constant.h"
#include "../Map/FarmMap.h"
#include "cocos2d.h"
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
    //����������Ϣ
    Festival* springFestival = Festival::create("Spring Festival", "Celebrate the arrival of Spring with games, food, and fun!", "Spring 7", true);
    if (springFestival) {
        festivals.push_back(springFestival);
    }

    Festival* summerFestival = Festival::create("Summer Festival", "The hot days of Summer are here! Time for the beach!", "Summer 15", false);
    if (summerFestival) {
        festivals.push_back(summerFestival);
    }

    Festival* fallFestival = Festival::create("Fall Festival", "Let's picking up the falling leaves!", "Fall 5", false);
    if (fallFestival) {
        festivals.push_back(fallFestival);
    }

    Festival* winterFestival = Festival::create("Winter Festival", "Merry Christmas and Happy Birthday to levi!", "Winter 25", false);
    if (winterFestival) {
        festivals.push_back(winterFestival);
    }
    currentYear = startYear;
    currentDay = startDay;

    dateLabel = Label::createWithTTF("", ResPath::FONT_TTF, 24);

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

// ����Ƿ��ǽ��գ����������ջ
void DateManage::checkFestivalEvent() {
    auto dateManager = DateManage::getInstance();
    const std::string currentDate = dateManager->getCurrentDate();
    for (auto& festival : festivals) {
        if (festival->getEventDate() == currentDate) {
            // ��ǰ�������������ƥ�䣬��ʼ���ջ
            festival->startEvent();
            break;
        }
    }
}

void DateManage::updateDate() {
    // ��ȡ DateManage ʵ��
    DateManage* dateManager = DateManage::getInstance();

    // ����һ��
    dateManager->advanceDay();

    // ��ȡ��ǰ����ݡ����ں�����
    int year = dateManager->getCurrentYear();
    std::string season = dateManager->getCurrentSeason();
    int day = dateManager->getCurrentDayInSeason();

    // ���������ַ���
    std::stringstream dateStream;
    dateStream << season << " " << day << " - Year " << year;

    // ���� Label
    dateLabel->setString(dateStream.str());

    checkFestivalEvent();
}