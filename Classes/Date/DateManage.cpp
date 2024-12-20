/****************************************************************
 * File Function: ʵ�����ڹ����࣬������ʾ��������Ϸ�����ڵļ��������
 * Author:        Τ��� ��׿�� ����
 ****************************************************************/
#include "DateManage.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
#include "cocos2d.h"
DateManage* DateManage::instance = nullptr;  // ���岢��ʼ��Ϊ nullptr

// ˽�й��캯������ֹ�ⲿֱ�Ӵ�������
DateManage::DateManage()  {}

// ��������
DateManage::~DateManage() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}

// ��ȡ����ʵ��
DateManage* DateManage::getInstance() {
    if (instance == nullptr) {
        instance = new (std::nothrow) DateManage();
        if (instance && instance->init(1, 1)) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
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

    // ���ڱ�ǩ
    dateLabel = cocos2d::Label::createWithTTF("", ResPath::FONT_TTF, 24);
    addChild(dateLabel);
    dateLabel->setPosition(cocos2d::Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // ���Ͻ�λ��
    
    // Ǯ��ǩ
    moneyLabel = cocos2d::Label::createWithTTF("", ResPath::FONT_TTF, 24);
    moneyLabel->setColor(Color3B::YELLOW);
    addChild(moneyLabel);
    moneyLabel->setPosition(cocos2d::Vec2(WINSIZE.width - 100, WINSIZE.height - 80));  // ���Ͻ�λ��
    
    // ��ʼ������Ϊ����
    currentWeater = Weather::Sunny;

    return true;
}

// ��ȡ��ǰ����
std::string DateManage::getCurrentDate() const {
    int dayInSeason = (currentDay - 1) % DAYSINSEASON + 1; // ��ǰ���ڵĵڼ���
    int seasonIndex = (currentDay - 1) / DAYSINSEASON % 4; // ��������

    std::stringstream dateStream;
    dateStream << SEASONNAME[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

// ��ȡ��ǰ����
std::string DateManage::getCurrentSeason() const {
    int seasonIndex = ((currentDay - 1) / DAYSINSEASON) % 4;
    return SEASONNAME[seasonIndex];
}

// ��ȡ��ǰ�����ڵ�ǰ�������ǵڼ���
int DateManage::getCurrentDayInSeason() const {
    return (currentDay - 1) % DAYSINSEASON + 1; // ��ǰ���ڵĵڼ���
}

// ��ȡ��ǰ�������������ǵڼ���
int DateManage::getCurrentDayInWeek() const {
    return (currentDay - 1) % DAYSINWEEK + 1; // ÿ�ܵ���һ��
}

// ��ȡ��ǰ����
int DateManage::getDay() const{
    return currentDay;
}

// ��ǰ��������һ��
void DateManage::advanceDay() {
    ++currentDay;
    if (currentDay > DAYSINYEAR) {
        currentDay = 1; // �µ�һ��
        ++currentYear;
    }
}

// �жϵ�ǰ�Ƿ�Ϊ�������
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

// ��ȡ�������
int DateManage::getSeasonIndex(const std::string& season) {
    auto it = SEASONINDEX.find(season);
        if (it != SEASONINDEX.end()) {
            return it->second;
        }
        else {
            return -1;
        }
}

// ��ȡ��ǰ���
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

// ��������
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

    // ����Label
    dateLabel->setString(dateStream.str());

    // ����money�ַ���
    Player* player = Player::getInstance();
    std::stringstream moneyStream;
    int money = player->getMoney();
    moneyStream << "Current Money: "<<money;
    moneyLabel->setString(moneyStream.str());

    checkFestivalEvent();

    // ��������
    updateCurrentWeather();
}

// ��ȡ��ǰ������
Weather DateManage::getCurrentWeather() const{
    return currentWeater;
}

// ����ÿ�������
void DateManage::updateCurrentWeather() {
    // ��ȡ��ǰ������
    std::string currentSeason = getCurrentSeason();

    // ÿ�����������ĸ���
    float sunnyProb = 0.6f;
    float lightRainProb = 0.2f;
    float heavyRainProb = (currentSeason == "Winter") ? 0.1f : 0.2f;

    // ���������
    float randomValue = static_cast<float>(rand()) / RAND_MAX;

    // ����������ж�����
    if (randomValue < sunnyProb) {
        currentWeater = Weather::Sunny;
    }
    else if (randomValue < sunnyProb + lightRainProb) {
        currentWeater = Weather::LightRain;
    }
    else if (randomValue < sunnyProb + lightRainProb + heavyRainProb) {
        currentWeater = Weather::HeavyRain;
    }
    else {
        currentWeater = Weather::Snowy;
    }
}