#ifndef __AXE_H__
#define __AXE_H__

#include "Tool.h"

// ��ͷ��
class Axe : public Tool {
public:
	// ��̬��������
	static Axe* create();

	// ��ʼ����ͷ
	bool init();

	// ʹ�ù���
	void useTool(const cocos2d::Vec2& targetPosition) override;
};

#endif
