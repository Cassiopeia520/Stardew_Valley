#include "PickAxe.h"
#include "../Player/Player.h"

USING_NS_CC;

Pickaxe* Pickaxe::create() {
	Pickaxe* pickaxe = new(std::nothrow) Pickaxe();
	if (pickaxe && pickaxe->init()) {
		pickaxe->autorelease();
		return pickaxe;
	}
	CC_SAFE_DELETE(pickaxe);
	return nullptr;
}

bool Pickaxe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("pickaxe");
}

void Pickaxe::useTool() {
	// ���Ÿ�ͷʹ�ö���
	auto rotationAction = RotateBy::create(0.2f, 90); // ˳ʱ����ת��ʮ�ȣ���ʱ0.2��
	auto resetRotationAction = RotateBy::create(0.2f, -90); // �ظ���ʼ�Ƕ�
	setVisible(true);
	// ��������
	auto sequence = Sequence::create(
		rotationAction,
		CallFunc::create([=]() {
			CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
			// todo ��������߼����������Ƿ�����Ŀ��
			}),
		resetRotationAction,
		nullptr
	);

	this->runAction(sequence);
	setVisible(false);
}