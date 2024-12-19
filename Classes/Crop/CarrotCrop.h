#ifndef __CARROTCROP_H__
#define __CARROTCROP_H__

#include "cocos2d.h"
#include "Crop.h"

/*
 * Class Name:     Carrot
 * Class Function: ���ܲ�������
 */
class Carrot : public Crop {
public:
	// ��̬��������
	static Carrot* create();

	// ��ʼ��
	bool init() override;

	// ���캯��
	Carrot();

	// ��������
	void grow() override;

	// ���������������
	void generatePest() override;
};


#endif
