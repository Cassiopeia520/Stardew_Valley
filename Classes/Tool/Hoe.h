#ifndef __HOE_H__
#define __HOE_H__

#include "Tool.h"

// ��ͷ��
class Hoe : public Tool {
public:
	static Hoe* create();

	// ��ʼ����ͷ
	bool init();

	// ʹ�ù���
	void useTool() override;
};

#endif
