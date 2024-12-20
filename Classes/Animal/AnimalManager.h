/****************************************************************
 * File Function: ũ������������ʵ�֣�ʵ��ũ���ϵĶ���Ĺ���
 * Author:        ����
 ****************************************************************/
#ifndef __ANIMAL_MANAGER_H__
#define __ANIMAL_MANAGER_H__

#include "cocos2d.h"
#include "Animal.h"
#include<vector>

// AnimalManager�ࣺũ���еĶ������
class AnimalManager :public cocos2d::Node {
public:
	// ��̬����
	static AnimalManager* create();

	// ��ӵ�������
	void addAnimal(Animal* animal, const cocos2d::Vec2& position);

	// �������ж���״̬
	void updateAnimals();

	// ι������
	void feedAnimal();
private:
	// ��������
	int animalCount;

	// ���캯��
	AnimalManager();

	// ��������
	virtual ~AnimalManager();

	// ũ�������Ķ���
	std::vector<Animal*> animals;
};

#endif 