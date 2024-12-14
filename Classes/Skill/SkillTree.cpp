#include "SkillTree.h"

USING_NS_CC;

// ���徲̬ʵ��ָ��
SkillTree* SkillTree::instance = nullptr;

// ��ȡ����ʵ��
SkillTree* SkillTree::getInstance() {
    if (!instance) {
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
    addSkill("Mining", new Skill("Mining", 5, [](int level) {}));

    addSkill("Fishing", new Skill("Fishing", 5, [](int level) {}));

    addSkill("Agriculture", new Skill("Agriculture", 5, [](int level) {}));

    addSkill("Cooking", new Skill("Cooking", 5, [](int level) {}));

    // test ���Լ�����ʾ,���������ɾ��
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Mining");
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");

    return true; // ���س�ʼ���ɹ�
}

// ��Ӽ���
void SkillTree::addSkill(const std::string& name, Skill* skill) {
    skills[name] = skill;
}

// ��������
bool SkillTree::levelUpSkill(const std::string& name) {
    // ��������
    return skills[name]->levelUp();
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

SkillTree::~SkillTree() {
    if (instance) {
        instance = nullptr;
    }
}