#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "Tool.h"

// ˮ����
class Kettle : public Tool {
private:

	// ˮ���ĺ�ˮ��
	int waterLevel;

public:
	// ��̬��������
	static Kettle* create();

	// ˮ���Ĺ��캯��
	Kettle();

	// ��ʼ��ˮ��
	bool init() override;

	// ʹ�ù���
	void useItem() override;

	// ��õ�ǰˮ�����ˮ��
	int Kettle::getCurrentWaterLevel() const;

	// ���䵱ǰˮ�����ˮ��
	void Kettle::refillWateringCan(int water);
};

#endif