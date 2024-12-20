/****************************************************************
 * File Function: ũ������ţ�࣬�̳���Animal�࣬ʵ��ũ���ϵ�ţ�Ŀ���
 * Author:        ����
 ****************************************************************/
#ifndef __COW_H__
#define __COW_H__

#include "Animal.h"
#include "cocos2d.h"
#include "../Behavior/MovementBehavior .h"

// Cow�ࣺ�̳���Animal
class Cow :public Animal {
public:
	// ��̬��Ա���������ڴ���������һ���µ� Cow ���Ͷ����ʵ��
	static Cow* create(cocos2d::Vec2 position);

	// ��ʼ������
	bool init() override;

private:
	// ���캯��
	Cow(cocos2d::Vec2 position);

	// ��������
	~Cow() ;

	// ������
	int milkProduction;

	// ��ʱ��key
	std::string moveScheduleKey;

	// �����ƶ�����
	void startMoving();

	// ִ��һ������ƶ�
	void performRandomMove(float dt);

	// �����ƶ���Ϊ
	void setMovementBehavior(MovementBehavior* behavior) override;

	// �ƶ���Ϊ
	MovementBehavior* movementBehavior;
};

#endif 
