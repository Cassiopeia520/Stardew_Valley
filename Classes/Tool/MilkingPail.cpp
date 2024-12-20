/****************************************************************
 * File Function: MilkingPail��ľ���ʵ��
 * Author:        ����
 ****************************************************************/
#include "MilkingPail.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// MilkPail�ࣺ��̬��������
MilkPail* MilkPail::create() {
	MilkPail* milkPail = new (std::nothrow) MilkPail();
	if (milkPail && milkPail->init()) {
		milkPail->autorelease();
		return milkPail;
	}
	CC_SAFE_DELETE(milkPail);
	return nullptr;
}

// MilkPail�ࣺ��ʼ������Ͱ
bool MilkPail::init() {
	// ���û���ĳ�ʼ������
	return Tool::init({ "milkPail", MILKPAIL });
}

// MilkPail�ࣺʹ�ù���
void MilkPail::useItem() {

}