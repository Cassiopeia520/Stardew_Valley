#ifndef __COW_H__
#define __COW_H__

#include "Animal.h"
#include "cocos2d.h"

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
};

#endif 
