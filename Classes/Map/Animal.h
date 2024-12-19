#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include "../Behavior/MovementBehavior .h"
#include<string>

/*
 * Class Name:     Animal
 * Class Function: ũ�����������
 */
class Animal : public cocos2d::Sprite {
public:
	// ��ȡ����λ��
	cocos2d::Vec2 getAnimalPosition();
	
	// ��ȡ��������
	std::string getAnimalName();

	// ��ʼ��
	virtual bool init();
protected:
	// ���캯��
	Animal(cocos2d::Vec2 position);

	// ��������
	virtual ~Animal();

	// �Ƿ񼢶�
	bool isHungry;
private:
	// ��������
	std::string animalName;

	// ����λ��
	cocos2d::Vec2 position;

	// �����ƶ�
	virtual void setMovementBehavior(MovementBehavior* behavior)=0;
};
#endif 
