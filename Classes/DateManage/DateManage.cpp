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

/*std::string DateManage::getNextFestival()
{
    std::string res = "Today is " + getCurrentDate() + "!\n";
    if (isFestivalDay()) {
        int dayInSeason = getCurrentDay();
        if (getCurrentSeason() == "Spring" && dayInSeason == 7)
            res += "Celebrate the arrival of Spring with games, food, and fun!\n";
        else if (getCurrentSeason() == "Summer" && dayInSeason == 15)
            res += "The hot days of Summer are here! Time for the beach!\n";
        else if (getCurrentSeason() == "Fall" && dayInSeason == 5)
            res += "Let's picking up the falling leaves!\n";
        else if (getCurrentSeason() == "Winter" && dayInSeason == 25)
            res += "Merry Christmas and Happy Birthday to levi!\n";
    }
        
    //FarmMap* farmMap = FarmMap::getInstance();
    for (Festival* festival : farmMap->festivals) {
        std::string season, day, curSeason;
        std::istringstream stream(festival->getEventDate());
        stream >> season; // ��ȡ����
        stream >> day;    // ��ȡ����
        int date = std::stoi(day);

        std::istringstream streamCur(getCurrentDate());
        streamCur >> curSeason >> day;
        if (season == getCurrentSeason() && date > std::stoi(day))
            return festival->getEventName() + "is coming soon!";
        else if (season > getCurrentSeason())
            return festival->getEventName() + "is coming soon!";
    }
    return "waiting for next year..";
}*/

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
