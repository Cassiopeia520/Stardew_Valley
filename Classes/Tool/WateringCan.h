#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "Tool.h"

// ˮ����
class Kettle : public Tool {
public:
	// ��̬��������
	static Kettle* create();

	// ��ʼ��ˮ��
	bool init();

	// ʹ�ù���
	void useTool() override;
};

#endif