#ifndef __PIG_H__
#define __PIG_H__

#include "Animal.h"
#include "cocos2d.h"

// Pig�ࣺ�̳���Animal
class Pig :public Animal {
public:
	// ��̬��Ա���������ڴ���������һ���µ�Pig���Ͷ����ʵ��
	static Pig* create(const cocos2d::Vec2& position);

	// ��ʼ������
	bool init() override;

	// ��õ�ǰ��¶����
	int getTruffleCount() const;
private:
	// ���캯��
	Pig(const cocos2d::Vec2& position);
	
	// ��������
	~Pig();

	// ��¶����
	int truffleCount;
};

#endif 