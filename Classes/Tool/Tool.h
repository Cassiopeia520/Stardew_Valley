#ifndef __TOOL_H__
#define __TOOL_H__
#include "../Item/Item.h"
#include "cocos2d.h"
#include <string>

// ������
class Tool : public Item {
public:
	// ��ʼ��
	virtual bool init(const std::string& name) override;

	// ʹ�ù���
	// virtual void useItem() override;

	virtual ~Tool() {}
};

#endif
