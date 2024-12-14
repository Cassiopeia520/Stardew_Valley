#include "SkillTreeUI.h"
#include "SkillTree.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
#include "../MyButton/MyButton.h"
USING_NS_CC;

bool SkillTreeUI::isOpen = false;

// ���徲̬ʵ��ָ��
SkillTreeUI* SkillTreeUI::instance = nullptr;

// ��ȡ����ʵ��
SkillTreeUI* SkillTreeUI::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) SkillTreeUI();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool SkillTreeUI::init() {
    isOpen = false;
    if (!Layer::init()) {
        return false;
    }
    setupUI();
    return true;
}

void SkillTreeUI::setupUI() {
    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ��ȡ������ʵ��
    auto skillTree = SkillTree::getInstance();

    // ���ñ���ͼƬ
    auto bg = Sprite::create(ResPath::COOP_PANEL);
    float bgWidth = visibleSize.width / 2;  // �������ռ��Ļ��һ��
    float bgHeight = visibleSize.height / 2; // �����߶�ռ��Ļ��һ��
    bg->setScaleX(bgWidth / bg->getContentSize().width);  // ���������ſ��
    bg->setScaleY(bgHeight / bg->getContentSize().height); // ���������Ÿ߶�
    bg->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y); // ������������Ļ����
    addChild(bg);

    // �������ݵ�ƫ������ȷ���ӱ���������ʼ
    int yOffset = bg->getPositionY() + bgHeight / 2 - 50; // �ӱ���������ʼ��ƫ����

    // ����������������UIԪ��
    for (const auto& skillPair : skillTree->getAllSkills()) {
        const std::string& skillName = skillPair.first;
        Skill* skill = skillPair.second;

        // �������Ʊ�ǩ
        auto skillLabel = Label::createWithTTF(skillName, ResPath::FONT_TTF, 24);
        skillLabel->setAnchorPoint(Vec2(0, 0.5)); // �����
        skillLabel->setPosition(bg->getPositionX() - bgWidth / 2 + 50, yOffset); // ����ڱ���λ��
        addChild(skillLabel);

        // ���㼼�ܵĽ���
        int currentLevel = skill->getCurrentLevel();
        int maxLevel = skill->getMaxLevel();

        // ��ȡÿ��������ռ���
        float levelWidth = bgWidth / 2 / maxLevel;

        // ������ʾÿ������
        for (int i = 0; i < currentLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_BACKGROUND); // ������ͼƬ
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // ˮƽ����
            addChild(levelBlock);

        }

        // ���ܵȼ���ǩ
        std::string levelText = StringUtils::format("Lv %d/%d", skill->getCurrentLevel(), skill->getMaxLevel());
        auto levelLabel = Label::createWithTTF(levelText, ResPath::FONT_TTF, 20);
        levelLabel->setPosition(bg->getPositionX() + bgWidth / 3, yOffset); // ���ܵȼ���ǩ����
        addChild(levelLabel);

        yOffset -= 80; // ÿ��֮����80
        setVisible(false);
    }

}


void SkillTreeUI::closeCallback(EventListenerMouse* listener) {
    _eventDispatcher->removeEventListener(listener);
    Player::getInstance()->stopAllActions();
    Player::getInstance()->stopMoving();
    setVisible(false);
    isOpen = false;
    Player::getInstance()->setUseItemEnable(true);
}

void SkillTreeUI::openSkillUI() {
    Player::getInstance()->setUseItemEnable(false);
    // �����رհ�ť
    auto closeButton = MyButton::create(ResPath::SKILL_CLOSE, ResPath::SKILL_CLOSE_ON);
    closeButton->setPosition(Vec2(WINSIZE.width * 3 / 4 - 25, WINSIZE.height * 3 / 4 - 25));
    addChild(closeButton, 2);

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [=](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && closeButton->isHover())
            closeCallback(listener);
        };
    if (this->getParent()) {
        // ��ӵ����ڵ�Control�����Ŀ����Ϊ�˽��͸ü����������¼������ȼ���ʹ��Player useItemEnable������Ч
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getParent());
    }
}

SkillTreeUI::~SkillTreeUI() {
    if (instance) {
        instance = nullptr;
    }
}
