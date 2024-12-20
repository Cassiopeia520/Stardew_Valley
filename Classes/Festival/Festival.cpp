/****************************************************************
 * File Function: ʵ�ֽ����࣬�̳�CommunityEvent�ಢ����ʵ�֣���Ϊ��Ϸ�н������
 * Author:        Τ���
 ****************************************************************/
#include "Festival.h"
#include "../Map/FarmMap.h"
#include "../Constant/Constant.h"

USING_NS_CC;

static std::vector<Festival*> festivals;  // ��̬��Ա����

// ��̬����
Festival* Festival::create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday) {
    Festival* instance = new Festival();
    if (instance && instance->init(name, description, date, isHoliday)) {
        return instance;
    }
    delete instance;
    return nullptr;
}

// ��ʼ������
bool Festival::init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday) {
    // ���ø���ĳ�ʼ��
    if (!CommunityEvent::init(name, description, date)) {
        return false;
    }

    // ��ʼ���������е�����
    holiday = isHoliday;
    return true;
}

// ��ʼ�
void Festival::startEvent() {
    // �����ı�����������
    std::string message = "The festival " + eventName + " has started!";

    // ����ǽڼ��գ��޸���Ϣ����
    if (holiday) {
        message = "It's a holiday! Enjoy your time off in " + eventName + "!";
    }
    else {
        message = "Join the community to celebrate the " + eventName + "!";
    }

    FarmMap* farmMap = FarmMap::getInstance();
    // ����һ���µ� Label ����ʾ��Ϣ
    auto label = Label::createWithTTF(message, ResPath::FONT_TTF, 46);
    if (label) {
        // ����λ��Ϊ��Ļ����
        label->setPosition(Vec2(WINSIZE.width / 2 - farmMap->getPosition().x, WINSIZE.height / 2 - farmMap->getPosition().y));
        label->setTextColor(Color4B::WHITE);

        // �� label ��ӵ�������
        farmMap->addChild(label, 12);

        // �����ӳ� 2 ���Ӻ��Ƴ��ı��Ķ���
        auto delay = DelayTime::create(2.0f);
        auto remove = CallFunc::create([label]() {
            label->removeFromParent();
            });

        // ��϶���������
        auto sequence = Sequence::create(delay, remove, nullptr);
        label->runAction(sequence);
    }
}

// �жϵ�ǰ�Ƿ�Ϊ����
bool Festival::isHoliday() const {
    return holiday;
}