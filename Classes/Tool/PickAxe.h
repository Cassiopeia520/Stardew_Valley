#ifndef __PICKAXE_H__H
#define __PICKAXE_H__H

#include "Tool.h"

// ʮ�ָ���
class Pickaxe : public Tool {
public:
	// ��̬��������
	static Pickaxe* create();

	// ��ʼ����ͷ
	bool init();

	// ʹ�ù���
	void useTool() override;
};

#endif
