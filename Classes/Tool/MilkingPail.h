#ifndef __MILKINGPAIL_H__
#define __MILKINGPAIL_H__

#include "cocos2d.h"
#include "Tool.h"

// MilkPail�ࣺ����Ͱ
class MilkPail : public Tool {
public:
	// ��̬��������
	static MilkPail* create();

	// ��ʼ������Ͱ
	bool init() override;

	// ʹ�ù���
	void useItem() override;
};
#endif