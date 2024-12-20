/****************************************************************
 * File Function: ũҩ��ľ���ʵ��
 * Author:        ����
 ****************************************************************/
#include "Agrochemical.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Agrochemical* Agrochemical::create() {
	Agrochemical* agrochemical = new (std::nothrow) Agrochemical();
	if (agrochemical && agrochemical->init()) {
		agrochemical->autorelease();
		return agrochemical;
	}
	CC_SAFE_DELETE(agrochemical);
	return nullptr;
}

bool Agrochemical::init() {
	// ���û���ĳ�ʼ������
	return Tool::init({ "agrochemical", AGROCHEMICAL });
}

// ʹ��ũҩ
void Agrochemical::useItem() {

}