#include "SkillTree.h"
#include "SkillTreeUI.h"

USING_NS_CC;

int SkillTree::plantingCount = 0;
int SkillTree::fishingCount = 0;
int SkillTree::miningCount = 0;
int SkillTree::cookingCount = 0;

// ���徲̬ʵ��ָ��
SkillTree* SkillTree::instance = nullptr;

// ��ȡ����ʵ��
SkillTree* SkillTree::getInstance() {
    if (instance == nullptr) {
        instance = new (std::nothrow) SkillTree();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// ��ʼ��������
bool SkillTree::init() {
    addSkill("Mining", Skill::create("Mining", 5, [](int level) {}));

    addSkill("Fishing", Skill::create("Fishing", 5, [](int level) {}));

    addSkill("Agriculture", Skill::create("Agriculture", 5, [](int level) {}));

    addSkill("Cooking", Skill::create("Cooking", 5, [](int level) {}));

    return true; // ���س�ʼ���ɹ�
}

// ��Ӽ���
void SkillTree::addSkill(const std::string& name, Skill* skill) {
    skills[name] = skill;
}

bool SkillTree::setSkillLevel(const std::string& name, const int level)
{
    return skills[name]->setLevel(level);
}

// ��ȡ����
Skill* SkillTree::getSkill(const std::string& name) const {
    if (skills.count(name)) {
        return skills.at(name);
    }
    return nullptr;
}

const std::map<std::string, Skill*>& SkillTree::getAllSkills() const {
    return skills;
}

void SkillTree::updatePlantingCount(int count)
{
    plantingCount += count;
    SkillTreeUI::getInstance()->updateUI();
}

void SkillTree::updateFishingCount(int count)
{
    fishingCount += count;
    SkillTreeUI::getInstance()->updateUI();
}

void SkillTree::updateMiningCount(int count)
{
    miningCount += count;
    SkillTreeUI::getInstance()->updateUI();
}

void SkillTree::updateCookingCount(int count)
{
    cookingCount += count;
    SkillTreeUI::getInstance()->updateUI();
}

SkillTree::~SkillTree() {
    if (instance) {
        instance = nullptr;
    }
}