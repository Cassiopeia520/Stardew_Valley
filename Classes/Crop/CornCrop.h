/****************************************************************
 * File Function: ���������࣬�̳���Crop������࣬ʵ�����׵������߼�
 * Author:        ����
 ****************************************************************/
#ifndef __CORNCROP_H__
#define __CORNCROP_H__

#include "cocos2d.h"
#include "Crop.h"

// �����������
class Corn : public Crop {
public:
	// ��̬��������
	static Corn* create();

	// ��ʼ��
	bool init() override;

	// ���캯��
	Corn();

	// ���׵���������
	void grow() override;

	// �����������
	void generatePest() override;
};

#endif // 
