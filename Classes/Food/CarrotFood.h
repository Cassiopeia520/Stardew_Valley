/****************************************************************
 * File Function: ���ܲ�ʳ���࣬�����������ܲ���Ʒ�ڱ����е�״̬
 * Author:        ����
 ****************************************************************/
#ifndef __CARROTFOOD_H__
#define __CARROTFOOD_H__

#include "cocos2d.h"
#include "Food.h"

// ���ܲ�ʳ����
class CarrotFood : public Food {
public:
	// ��̬��������
	static CarrotFood* create();

	// ��ʼ�����ܲ�ʳ��
	bool init() override;
};
#endif 