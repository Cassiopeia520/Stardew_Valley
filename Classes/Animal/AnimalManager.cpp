/****************************************************************
 * File Function: ũ����������࣬ʵ��ũ���ϵĶ���Ĺ���
 * Author:        ����
 ****************************************************************/
#include "AnimalManager.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// AnimalManager�ࣺ���캯��
AnimalManager::AnimalManager() :
	animalCount(0){
}

// AnimalManager�ࣺ��������
AnimalManager::~AnimalManager() {
}

// ��̬����
AnimalManager* AnimalManager::create() {
	AnimalManager* animalManager = new AnimalManager();
	if (animalManager && animalManager->init()) {
		animalManager->autorelease();
		return animalManager;
	}

	CC_SAFE_DELETE(animalManager);
	return nullptr;
}

// AnimalManager�ࣺ����������Ӷ���
void AnimalManager::addAnimal(Animal* animal, const cocos2d::Vec2& position) {

	// �ж��Ƿ�Ϊ��
	if (animal == nullptr) {
		return;
	}
	// ��Ӷ���
	animals.push_back(animal);
	addChild(animal,static_cast<int>(animals.size()));
	animal->setPosition(position);
}


// AnimalManager�ࣺ�������ж����״̬
void AnimalManager::updateAnimals() {

}

// AnimalManager�ࣺι������
void AnimalManager::feedAnimal() {

}