/****************************************************************
 * File Function: ʵ��ʮ�ָ��࣬�̳���Tool,ʮ�ָ�����ڿ��ʯͷ
 * Author:        Τ��� ��׿��
 ****************************************************************/
#ifndef __PICKAXE_H__
#define __PICKAXE_H__

#include "Tool.h"

// ʮ�ָ���
class Pickaxe : public Tool {
public:
	// ��̬��������
	static Pickaxe* create();

	// ��ʼ��ʮ�ָ�
	bool init();

	// ʹ�ù���
	void useItem() override;
};
#endif