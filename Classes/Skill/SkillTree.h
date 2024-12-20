#ifndef __SKILLTREE_H__
#define __SKILLTREE_H__

#include "Skill.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "cocos2d.h"

class SkillTree : public cocos2d::Node{
public:
    // ��ȡȫ��Ψһʵ��
    static SkillTree* getInstance();

    // ��ʼ��������
    bool init();

    // ��Ӽ���
    void addSkill(const std::string& name, Skill* skill);

    // ���ü��ܵȼ�
    bool setSkillLevel(const std::string& name, const int level);

    // ��ȡ����
    Skill* getSkill(const std::string& name) const;

    // ��ȡ���м��ܵķ���
    const std::map<std::string, Skill*>& getAllSkills() const;

    //��ֲ������get��update
    void updatePlantingCount(int count);
    int getPlantingCount() { return plantingCount; }

    //���������get��update
    void updateFishingCount(int count);
    int getFishingCount() { return fishingCount; }

    //�ɿ������get��update
    void updateMiningCount(int count);
    int getMiningCount() { return miningCount; }

    //��⿴�����get��update
    void updateCookingCount(int count);
    int getCookingCount() { return cookingCount; }

private:
    // ���캯��˽�л�����ֹ�ⲿֱ�Ӵ���
    SkillTree() = default;

    // ��������
    ~SkillTree();

    // ��̬ʵ��
    static SkillTree* instance;

    // ���ܴ洢
    std::map<std::string, Skill*> skills;

    // ��ֲ����������npc��������
    static int plantingCount;

    // �������
    static int fishingCount;

    // �ɿ����
    static int miningCount;

    // ��⿴���
    static int cookingCount;
};
#endif __SKILLTREE_H__