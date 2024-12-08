#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include<vector>

// ���������
enum AnimalType {
	CATTLE,			// ţ
	CHICKEN,		// ��
	SHEEP,			// ��
	PIG,			// ��
};

// �����Ʒ���б�
enum ProductType {
	BEEF,			// ţ��
	EGG,			// ����
	WOOL,			// ��ë
	MUTTON,			// ����
	PORK,			// ����
};

// ����Ļ���
class Animal : public cocos2d::Sprite{
private:
	AnimalType animalType;				// ���������
	int age;							// ���������
	cocos2d::Vec2 position;				// �����λ��
	std::vector<ProductType> product;	// �����ջ�Ĳ�Ʒ
	int growthDay;						// ����ĳɳ�����
	int maxGrowthDay;					// ����ĳ�������
	bool isMature;						// �����Ƿ����

protected:

public:

	// �ջ�
};

// Cattle���ʾţ���̳���Animal
class Cattle : public Animal {
private:

public:

};

// Chicken���ʾ�����̳���Animal
class Chicken : public Animal {
private:

public:

};

// Sheep���ʾ�򣬼̳���Animal
class Sheep : public Animal {
private:

public:

};

// Pig���ʾ���̳���Animal
class Pig : public Animal {
private:

public:

};

#endif
