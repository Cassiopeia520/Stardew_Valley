/****************************************************************
 * File Function: ������, �̳�Tool��
 * Author:        Τ���
 ****************************************************************/
#ifndef __SCYTHE_H__
#define __SCYTHE_H__

#include "Tool.h"

// ������
class Scythe : public Tool {
public:
	// ��̬��������
	static Scythe* create();

	// ��ʼ��
	bool init();

	// ʹ�ù���
	void useItem() override;
};

#endif