#ifndef __CORNFOOD_H__
#define __CORNFOOD_H__

#include "cocos2d.h"
#include "Food.h"

/*
 * Class Name:     CornFood
 * Class Function: ����ʳ����
 */
class CornFood : public Food {
public:
	// ��̬��������
	static CornFood* create();

	// ��ʼ������ʳ��
	bool init() override;
};
#endif