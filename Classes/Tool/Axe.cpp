#include "Axe.h"

USING_NS_CC;

Axe* Axe::create() {
	Axe* axe = new (std::nothrow) Axe();
	if (axe && axe->init()) {
		axe->autorelease();
		return axe;
	}
	CC_SAFE_DELETE(axe);
	return nullptr;
}

bool Axe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("axe");
}

void Axe::useTool(const Vec2& targetPosition) {
	// ���Ÿ�ͷʹ�ö�����ʾ��ʵ�֣�
	auto chopAction = Sequence::create(
		MoveTo::create(0.1f, targetPosition), // �ƶ���Ŀ��λ��
		CallFunc::create([=]() {
			CCLOG("Chopping at position (%f, %f)", targetPosition.x, targetPosition.y);
			}),
		MoveTo::create(0.1f, this->getPosition()), // ����ԭλ��
		nullptr
	);
	this->runAction(chopAction);
}