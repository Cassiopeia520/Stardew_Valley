#ifndef __CARROTFOOD_H__
#define __CARROTFOOD_H__

#include "cocos2d.h"
#include "Food.h"

/*
 * Class Name:     CarrotFood
 * Class Function: ���ܲ�ʳ����
 */
class CarrotFood : public Food {
public:
	// ��̬��������
	static CarrotFood* create();

	// ��ʼ�����ܲ�ʳ��
	bool init() override;
};
#endif 