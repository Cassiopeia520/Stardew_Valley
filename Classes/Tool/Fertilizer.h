/****************************************************************
 * File Function: �����࣬���ڳ�ʼ����Ʒ�еķ���
 * Author:        ����
 ****************************************************************/
#ifndef __FERTILIZER_H_
#define __FERTILIZER_H_

#include "Tool.h"

// Fertilizer��
class Fertilizer : public Tool {
public:
	static Fertilizer* create();

	// ��ʼ������
	bool init() override;

	// ʹ�ù���
	void useItem() override;
};
#endif