#include "Skill.h"

// ���캯��
Skill::Skill(const std::string& name, int maxLevel, std::function<void(int)> effect)
    : name(name), maxLevel(maxLevel), effect(effect) {
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

// ��������
bool Skill::levelUp() {
    if (currentLevel < maxLevel) {
        ++currentLevel;
        if (effect) {
            effect(currentLevel); // ִ�м���Ч��
        }
        return true;
    }
    return false;
}
