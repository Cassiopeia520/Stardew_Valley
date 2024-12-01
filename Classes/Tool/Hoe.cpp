#include "Hoe.h"
#include "../Player/Player.h"

USING_NS_CC;

Hoe* Hoe::create() {
	Hoe* hoe = new (std::nothrow) Hoe();
	if (hoe && hoe->init()) {
		hoe->autorelease();
		return hoe;
	}
	CC_SAFE_DELETE(hoe);
}

bool Hoe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("hoe");
}

void Hoe::useTool() {
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