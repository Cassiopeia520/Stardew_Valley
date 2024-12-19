#ifndef __SHEEP_H__
#define __SHEEP_H__

#include "Animal.h"
#include "cocos2d.h"

// Sheep�ࣺ�̳���Animal
class Sheep : public Animal {
public:
	// ��̬��Ա���������ڴ���������һ���µ�Sheep���Ͷ����ʵ��
	static Sheep* create(const cocos2d::Vec2& position);

	// ��ʼ������
	bool init() override;

	// ��ȡ��ë����
	int getWoolProduction() const;
private:
	// ���캯��
	Sheep(const cocos2d::Vec2& position);

	// ��������
	~Sheep();

	// ��ë����
	int woolProduction;

	// �����ƶ���Ϊ
	void setMovementBehavior(MovementBehavior* behavior) override;

	// �ƶ���Ϊ
	MovementBehavior* movementBehavior;
};

#endif 
