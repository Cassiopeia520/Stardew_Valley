/****************************************************************
 * File Function: �����࣬��ΪPLayerӵ�е�����
 * Author:        Τ���
 ****************************************************************/
#ifndef __SKILL_H
#define __SKILL_H
#include <string>
#include <functional>

class Skill {
public:
    // ��ʼ������
    bool init(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // ��������
    static Skill* create(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // ��ȡ��������
    const std::string& getName() const;

    // ��ȡ�������ȼ�
    int getMaxLevel() const;

    // ��ȡ���ܵ�ǰ�ȼ�
    int getCurrentLevel() const;

    // ���ü��ܵȼ�
    bool setLevel(int level);

private:
    std::string name;                 // ��������
    int maxLevel;                     // ���ܵ����ȼ�
    int currentLevel;             // ��ǰ���ܵȼ�
    std::function<void(int)> effect;  // ����Ч�������뵱ǰ�ȼ�
};

#endif __SKILL_H