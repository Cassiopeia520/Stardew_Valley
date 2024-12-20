/****************************************************************
 * File Function: �������ڳ�����չʾ�࣬����ʵ�ּ���������ʾ�����
 * Author:        Τ��� ��׿��
 ****************************************************************/
#include "SkillTreeUI.h"
#include "SkillTree.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
#include "../MyButton/MyButton.h"
#include "../Map/FarmMap.h"
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

// ��ʼ��
bool SkillTreeUI::init() {
    isOpen = false;
    if (!Layer::init()) {
        return false;
    }
    setupUI();
    return true;
}

// ����
void SkillTreeUI::updateUI()
{
    SkillTree* skillTree = SkillTree::getInstance();
    // ÿ5������
    skillTree->setSkillLevel("Agriculture", skillTree->getPlantingCount() / 5);
    skillTree->setSkillLevel("Fishing", skillTree->getFishingCount() / 5);
    skillTree->setSkillLevel("Mining", skillTree->getMiningCount() / 5);
    skillTree->setSkillLevel("Cooking", skillTree->getCookingCount() / 5);
    setupUI();
}

// չʾ����UI
void SkillTreeUI::setupUI() {
    // ��ȡ������ʵ��
    auto skillTree = SkillTree::getInstance();

    // ���ñ���ͼƬ
    auto bg = Sprite::create(ResPath::COOP_PANEL);
    float bgWidth = WINSIZE.width / 2;  // �������ռ��Ļ��һ��
    float bgHeight = WINSIZE.height / 2; // �����߶�ռ��Ļ��һ��
    bg->setScaleX(bgWidth / bg->getContentSize().width);  // ���������ſ��
    bg->setScaleY(bgHeight / bg->getContentSize().height); // ���������Ÿ߶�
    bg->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // ������������Ļ����
    addChild(bg);

    // �������ݵ�ƫ������ȷ���ӱ���������ʼ
    int yOffset = bg->getPositionY() + bgHeight / 2 - 50; // �ӱ���������ʼ��ƫ����

    // ����������������UIԪ��
    for (const auto& skillPair : skillTree->getAllSkills()) {
        const std::string& skillName = skillPair.first;
        Skill* skill = skillPair.second;

        // �������Ʊ�ǩ
        auto skillLabel = Label::createWithTTF(skillName, ResPath::FONT_TTF, 24);
        skillLabel->setTextColor(cocos2d::Color4B(0, 0, 0, 255));
        skillLabel->setAnchorPoint(Vec2(0, 0.5)); // �����
        skillLabel->setPosition(bg->getPositionX() - bgWidth / 2 + 50, yOffset); // ����ڱ���λ��
        addChild(skillLabel);

        // ���㼼�ܵĽ���
        int currentLevel = skill->getCurrentLevel();
        int maxLevel = skill->getMaxLevel();

        // ��ȡÿ��������ռ���
        float levelWidth = bgWidth / 2 / maxLevel;

        // ������ʾÿ������
        for (int i = 0; i < maxLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_BACKGROUND); // ������ͼƬ
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // ˮƽ����
            addChild(levelBlock);

        }

        for (int i = 0; i < currentLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_FOREGROUND); // ǰ����ͼƬ
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // ˮƽ����
            addChild(levelBlock);

        }

        // ���ܵȼ���ǩ
        std::string levelText = StringUtils::format("Lv %d/%d", skill->getCurrentLevel(), skill->getMaxLevel());
        auto levelLabel = Label::createWithTTF(levelText, ResPath::FONT_TTF, 20);
        levelLabel->setTextColor(cocos2d::Color4B(0, 0, 0, 255));
        levelLabel->setPosition(bg->getPositionX() + bgWidth / 3, yOffset); // ���ܵȼ���ǩ����
        addChild(levelLabel);

        yOffset -= 80; // ÿ��֮����80
        setVisible(false);
    }

}

// �رհ�ť�Ļص�����
void SkillTreeUI::closeCallback(EventListenerMouse* listener) {
    _eventDispatcher->removeEventListener(listener);
    Player::getInstance()->stopAllActions();
    Player::getInstance()->stopMoving();
    setVisible(false);
    isOpen = false;
    Player::getInstance()->setUseItemEnable(true);
}

// ��UI����
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

// ��������
SkillTreeUI::~SkillTreeUI() {
    if (instance) {
        instance = nullptr;
    }
}
