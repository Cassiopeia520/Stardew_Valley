#ifndef __SEED_H__
#define __SEED_H__

#include "Tool.h"
#include "cocos2d.h"

// Seed�ࣺ�̳��Թ����࣬��ʾ��Ʒ�е�����
class Seed : public Tool {
private:
public:
	// ��̬��������
	static Seed* create();

	// ��ʼ������
	bool init();

	// ʹ�ù���
	void useTool() override;
};

#endif
