/****************************************************************
 * File Function: ũ�����Ｆ�࣬�̳���Animal�࣬ʵ��ũ���ϵļ��Ŀ���
 * Author:        ����
 ****************************************************************/
#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "Animal.h"

// Chicken�ࣺ�̳���Animal
class Chicken : public Animal {
public:
	// ��̬��Ա���������ڴ���������һ���µ� Cow ���Ͷ����ʵ��
	static Chicken* create(const cocos2d::Vec2& position);

	// ��ʼ������
	bool init() override;
private:
	// ���캯��
	Chicken(const cocos2d::Vec2& position);

	// ��������
	~Chicken();

	// �µ�����
	int eggCount;

	// �����ƶ���Ϊ
	void setMovementBehavior(MovementBehavior* behavior) override;

	// �ƶ���Ϊ
	MovementBehavior* movementBehavior;
};

#endif 
