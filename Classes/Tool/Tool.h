#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include <string>

class Tool : public cocos2d::Sprite {
public:
	// ��ʼ������
	virtual bool init(const std::string& name);

	// ʹ�ù���
	virtual void useTool();

	// ��ȡ��������
	std::string getToolName() const {
		return toolName;
	}

protected:
	std::string toolName;
};

#endif
