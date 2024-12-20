/****************************************************************
 * File Function: ������ľ���ʵ��
 * Author:        ����
 ****************************************************************/
#include "Fertilizer.h"

USING_NS_CC;

Fertilizer* Fertilizer::create() {
	Fertilizer* fertilizer = new(std::nothrow) Fertilizer();
	if (fertilizer && fertilizer->init()) {
		fertilizer->autorelease();
		return fertilizer;
	}
	CC_SAFE_DELETE(fertilizer);
	return nullptr;
}

// 
bool Fertilizer::init() {
	// ���û���ĳ�ʼ������
	return Tool::init({ "fertilizer", FERTILIZER});
}

// ʹ�÷���
void Fertilizer::useItem() {

}