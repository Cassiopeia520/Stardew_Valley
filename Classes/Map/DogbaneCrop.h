#ifndef __DOGBANE_CROP_H__
#define __DOGBANE_CROP_H__

#include "cocos2d.h"
#include "Crop.h"

/*
 * Class Name:     Dogbane
 * Class Function: �����������
 */
class Dogbane : public Crop {
public:
	// ��̬��������
	static Dogbane* create();

	// ��ʼ��
	bool init() override;

	// ���캯��
	Dogbane();

	// ��������
	void grow() override;

	// ��������
	void generatePest() override;
};

#endif 