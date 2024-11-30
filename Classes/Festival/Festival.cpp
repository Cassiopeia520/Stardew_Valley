#include "Festival.h"
#include "../Map/FarmMap.h"

// ��̬��������
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
void Festival::startEvent(DateManage* dateManage) {

    // ��ȡ��Ļ�ߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����ı�����������
    std::string message = "The festival " + eventName + " has started!";

    // ����ǽڼ��գ��޸���Ϣ����
    if (holiday) {
        message = "It's a holiday! Enjoy your time off!";
    }
    else {
        message = "Join the community to celebrate the event!";
    }

    FarmMap* farmMap = FarmMap::getInstance();
    // ����һ���µ� Label ����ʾ��Ϣ
    auto label = cocos2d::Label::createWithTTF(message, "fonts/Marker Felt.ttf", 36);
    if (label) {
        // ����λ��Ϊ��Ļ����
        label->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        label->setTextColor(cocos2d::Color4B::WHITE);

        // �� label ��ӵ�������
        farmMap->addChild(label, 12);

        // �����ӳ� 2 ���Ӻ��Ƴ��ı��Ķ���
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto remove = cocos2d::CallFunc::create([label]() {
            label->removeFromParent();
            });

        // ��϶���������
        auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
        label->runAction(sequence);
    }
}

bool Festival::isHoliday() const {
    return holiday;
}

Festival::Festival()
{
}
