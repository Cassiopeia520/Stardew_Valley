#include "DateManage.h"

// 私有构造函数，防止外部直接创建对象
DateManage::DateManage() : currentYear(0), currentDay(0) {
    // 初始化
}

DateManage* DateManage::instance = nullptr;  // 定义并初始化为 nullptr

DateManage::~DateManage() {
    // 清理资源（如果有的话）
}

// 获取单例实例
DateManage* DateManage::getInstance() {
    if (instance == nullptr) {
        instance = new DateManage();  // 如果实例不存在，创建一个新的实例
        instance->init(1, 1);  // 默认初始化年份为1，日期为第 1 天
    }
    return instance;
}

// 创建新的 DateManage 实例，并指定开始年份和日期
DateManage* DateManage::create(int startYear, int startDay) {
    DateManage* instance = new DateManage();
    if (instance && instance->init(startYear, startDay)) {
        return instance;  // 如果初始化成功，则返回实例
    }
    delete instance;  // 否则删除实例
    return nullptr;
}

// 初始化方法
bool DateManage::init(int startYear, int startDay) {
    currentYear = startYear;
    currentDay = startDay;
    return true;
}

std::string DateManage::getCurrentDate() const {
    int dayOfYear = currentDay % daysInYear;
    int dayInSeason = dayOfYear % daysInSeason + 1; // 当前季节的第几天
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
    return currentDay % daysInSeason + 1; // 当前季节的第几天
}

int DateManage::getCurrentWeekday() const {
    return currentDay % daysInWeek; // 每周的哪一天
}

void DateManage::advanceDay() {
    currentDay++;
    if (currentDay >= daysInYear) {
        currentDay = 0; // 新的一年
        currentYear++;
    }
}

bool DateManage::isFestivalDay() const {
    // 节日出现在每个季节的特定日期
    int dayInSeason = getCurrentDay();
    if ((getCurrentSeason() == "Spring" && dayInSeason == 7) ||
        (getCurrentSeason() == "Summer" && dayInSeason == 15) ||
        (getCurrentSeason() == "Fall" && dayInSeason == 5) ||
        (getCurrentSeason() == "Winter" && dayInSeason == 25)) {
        return true;
    }
    return false;
}

std::string DateManage::getNextFestival()
{
    if (isFestivalDay())
        return "Today is " + getCurrentDate() + "!";
    FarmMap* farmMap = FarmMap::getInstance();
    for (Festival* festival : farmMap->festivals) {
        std::string season, day, curSeason;
        std::istringstream stream(festival->getEventDate());
        stream >> season; // 读取季节
        stream >> day;    // 读取日期
        int date = std::stoi(day);

        std::istringstream streamCur(getCurrentDate());
        streamCur >> curSeason >> day;
        if (season == getCurrentSeason() && date > std::stoi(day))
            return festival->getEventName() + "is coming soon!";
        else if (season > getCurrentSeason())
            return festival->getEventName() + "is coming soon!";
    }
    return "";
}

int DateManage::getSeasonIndex(const std::string& season) {
    // 映射季节字符串到整数
    static std::map<std::string, int> seasonMap = {
        {"Spring", 0},
        {"Summer", 1},
        {"Fall", 2},
        {"Winter", 3}
    };

    // 查找并返回季节的索引
    auto it = seasonMap.find(season);
    if (it != seasonMap.end()) {
        return it->second;
    }
    return -1; // 如果季节无效，返回 -1
}
int DateManage::getCurrentYear() const {
    return currentYear;
}
