/****************************************************************
 * File Function: Ѳ���ƶ������࣬�̳����ƶ����ƻ��࣬���ƾ������Ź̶�·���ƶ�
 * Author:        ����
 ****************************************************************/
#ifndef __PATROLMOVEMENT_H__
#define __PATROLMOVEMENT_H__

#include "cocos2d.h"
#include "MovementBehavior .h"
#include "../Animal/Animal.h"
#include <vector>

// Ѳ���ƶ�������
class PatrolMovement : public MovementBehavior {
public:
    // ��̬���캯��������·����
    static PatrolMovement* create(const std::vector<cocos2d::Vec2>& patrolPoints, float speed, bool loop = true);

    // ��ʼ��
    bool init(const std::vector<cocos2d::Vec2>& patrolTrailPoints, float patrolSpeed, bool patrolLoop = true);

    // ���캯��
    PatrolMovement();

    // ��������
    virtual ~PatrolMovement();

    // ִ���ƶ���Ϊ����
    void execute(Animal* animal);

    // ����Ӱ��
    void weatherChanged(float& radius, float& moveDuration) override;

private:
    // Ѳ��·����
    std::vector<cocos2d::Vec2> patrolPoints;

    // �ƶ��ٶȣ�����/�룩
    float baseSpeed;

    // �Ƿ�ѭ��Ѳ��
    bool loop;

    // ��ǰĿ��·��������
    size_t currentPointIndex;

    // ����ĳ�ʼλ��
    cocos2d::Vec2 initialPosition;

    // �����ƶ�ʵ��
    void moveToNextPoint(Animal* animal);

    // �߽��⣬ȷ��Ŀ��λ���ڵ�ͼ��
    cocos2d::Vec2 clampPosition(const cocos2d::Vec2& position, const cocos2d::Size& mapSize);
};

#endif // __PATROLMOVEMENT_H__