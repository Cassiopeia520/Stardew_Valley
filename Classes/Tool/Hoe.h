/****************************************************************
 * File Function: ʵ�ֳ�ͷ�࣬�̳���Tool����������
 * Author:        ��׿��
 ****************************************************************/
#ifndef __HOE_H__
#define __HOE_H__

#include "Tool.h"

// ��ͷ��
class Hoe : public Tool {
public:
	// ��̬��ʼ������
	static Hoe* create();

	// ��ʼ����ͷ
	bool init() override;

	// ʹ�ù���
	void useItem() override;
};
#endif
