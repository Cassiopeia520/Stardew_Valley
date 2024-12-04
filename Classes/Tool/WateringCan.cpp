#include "WateringCan.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Kettle* Kettle ::create() {
	Kettle *kettle = new(std::nothrow) Kettle();
	if (kettle && kettle->init()) {
		kettle->autorelease();
		return kettle;
	}
	CC_SAFE_DELETE(kettle);
	return nullptr;
}

bool Kettle::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("wateringCan");
}

// ʹ�ù���
void Kettle::useTool() {

}