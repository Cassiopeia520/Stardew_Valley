/****************************************************************
 * File Function: ũ�������������ʵ��
 * Author:        ����
 ****************************************************************/
#include "Animal.h"

USING_NS_CC;

// ��ö���λ��
Vec2 Animal::getAnimalPosition() {
	return position;
}

// ��ö�������
std::string Animal::getAnimalName() {
	return animalName;
}

// ��ʼ��
bool Animal::init() {
	return true;
}

// ���캯��
Animal::Animal(Vec2 position) :
	position(position), isHungry(true){
}

// ��������
Animal::~Animal() {

}