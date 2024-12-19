#include "Skill.h"

bool Skill::init(const std::string& name, int maxLevel, std::function<void(int)> effect)
{
    this->name = name;
    this->maxLevel = maxLevel;
    this->effect = effect;
    this->currentLevel = 0;

    if (name.empty() || maxLevel <= 0) {
        return false; 
    }

    return true; // ��ʼ���ɹ�
}

Skill* Skill::create(const std::string& name, int maxLevel, std::function<void(int)> effect) {
    Skill* skill = new Skill();  // �����µ� Skill ʵ��
    if (skill && skill->init(name, maxLevel, effect)) {  // ���� init �������г�ʼ��
        return skill;  // ��ʼ���ɹ�������ʵ��
    }
    else {
        delete skill;  // �����ʼ��ʧ�ܣ�ɾ��ʵ�������� nullptr
        return nullptr;
    }
}

// ��ȡ��������
const std::string& Skill::getName() const {
    return name;
}

// ��ȡ�������ȼ�
int Skill::getMaxLevel() const {
    return maxLevel;
}

// ��ȡ���ܵ�ǰ�ȼ�
int Skill::getCurrentLevel() const {
    return currentLevel;
}

bool Skill::setLevel(int level)
{
    if (level >= 0 && level <= maxLevel) {
        currentLevel = level;
        return true;
    }
    else if (level > maxLevel) {
        currentLevel = maxLevel;
        return true;
    }
    return false;
}
