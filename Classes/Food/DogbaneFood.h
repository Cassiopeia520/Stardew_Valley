/****************************************************************
 * File Function: �������Ʒ�࣬��������������ڱ����е�״̬
 * Author:        ����
 ****************************************************************/
#ifndef __DOGBANEFOOD_H__
#define __DOGBANEFOOD_H__

#include "cocos2d.h"
#include "Food.h"

// �������Ʒ��
class DogbaneFood : public Food {
public:
	// ��̬��������
	static DogbaneFood* create();

	// ��ʼ�������ʳ��
	bool init() override;

};
#endif // !__DOGBANEFOOD_H__
