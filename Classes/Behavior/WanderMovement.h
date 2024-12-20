/****************************************************************
 * File Function: �����ƶ��࣬�̳����ƶ����ƻ��࣬���ƾ��������ƶ�
 * Author:        ����
 ****************************************************************/
#ifndef __WANDERMOVEMENT_H__
#define __WANDERMOVEMENT_H__

#include "cocos2d.h"
#include "MovementBehavior .h"
#include "../Animal/Animal.h"

// �����ƶ�������
class WanderMovement : public MovementBehavior {
public:
	// ��̬���캯��
	static WanderMovement* create(float radius,float interval);

	// ��ʼ��
	bool init(float radius , float interval );

	// ���캯��
	WanderMovement();

	// ��������
	virtual ~WanderMovement();

	// ִ���ƶ���Ϊ����
	void execute(Animal* animal) ;

	// ����Ӱ��
	void weatherChanged(float& radius, float& moveDuration) override;
private:
	// �ƶ�����
	float moveRadius;

	// �ƶ����
	float moveInterval;

	// ����ĳ�ʼλ��
	cocos2d::Vec2 initialPosition;

	// �����ƶ�ʵ��
	void performRandomMove(Animal* animal);

	// ��ʱ��key
	std::string moveScheduleKey;
};
#endif 