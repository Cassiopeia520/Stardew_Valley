#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"

class Bag : public cocos2d::Node {
public:
	// ��������ʵ��
	static Bag* create();

	// ��ʼ������
	bool init();

	// ��ӹ��ߵ�����
	bool addTool(Tool* tool);

	// �Ƴ�����
	void removeTool(int index);

	// ��ȡĳ������
	Tool* getTool(int index) const;

	// ����ѡ�еĹ���
	void selectTool(int index);

	// ��ȡ��ǰѡ�еĹ���
	Tool* getSelectedTool() const;

private:
	// �洢���ߵ�����
	std::vector<Tool*> tools;

	// ��������
	static const int capacity = 9;

	// ��ǰѡ�еĹ�������
	int selectedIndex;

	// ������ʾ�����ľ��ο�͹���
	cocos2d::DrawNode* bagBackground; // ������
	std::vector<cocos2d::Sprite*> toolIcons; // ����ͼ��

	void updateDisplay();

	static const int iconSize = 54; // ÿ��ͼ��Ŀ��/�߶�
	static const int spacing = 10; // ͼ����
};
#endif __BAG_H__