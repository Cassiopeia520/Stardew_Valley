#ifndef __PICKAXE_H__
#define __PICKAXE_H__

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
