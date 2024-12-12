#pragma once
#include <string>
#include <functional>

class Skill {
public:
    // ���캯��
    Skill(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // ��ȡ��������
    const std::string& getName() const;

    // ��ȡ�������ȼ�
    int getMaxLevel() const;

    // ��ȡ���ܵ�ǰ�ȼ�
    int getCurrentLevel() const;

    // ��������
    bool levelUp();

private:
    std::string name;                 // ��������
    int maxLevel;                     // ���ܵ����ȼ�
    int currentLevel = 0;             // ��ǰ���ܵȼ�
    std::function<void(int)> effect;  // ����Ч�������뵱ǰ�ȼ�
};
