#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include "../Map/FarmMap.h"
#include <string>

// ������
class Tool : public cocos2d::Sprite {
public:
	// ��̬��������
	static Tool* create(const std::string& name);

	// ��ʼ��
	virtual bool init(const std::string& name);

	// ʹ�ù���
	virtual void useTool();

	// ��ȡ��������
	std::string getToolName() {
		return toolName;
	}
	// ��������
	std::string toolName;
protected:

};

#endif
