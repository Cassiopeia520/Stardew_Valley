/****************************************************************
 * File Function: ũҩ�࣬�̳���Tool��
 * Author:        ����
 ****************************************************************/
#ifndef __AGROCHEMICAL_H__
#define __AGROCHEMICAL_H__

#include "cocos2d.h"
#include "Tool.h"

// ũҩ��
class Agrochemical : public Tool {
public:
	// ��̬��������
	static Agrochemical* create();

	// ��ʼ��ũҩ
	bool init() override;

	// ʹ�ù���
	void useItem() override;
};

#endif // !__AGROCHEMICAL_H__
