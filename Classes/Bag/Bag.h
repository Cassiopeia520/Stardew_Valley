#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"

class Bag : public cocos2d::Node {
public:
	// ����ģʽ��ȡ����ʵ��
	static Bag* getInstance();

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

	// ��ʾ����
	void updateDisplay();

	// ��ǰ��ӵ�еĹ���
	std::vector<Tool*> tools;

	// �������Ŀ���
	void toggleToolBar(bool show);

private:
	// ����ʵ��
	static Bag* instance;

	// ˽�й��캯������ֹ���ʵ������ȷ��Ψһ��
	Bag();
	~Bag();

	// ��ֹ�����͸�ֵ
	Bag(const Bag&) = delete;
	Bag& operator=(const Bag&) = delete;

	// �洢���ߵ�����

	// ��������
	static const int capacity = 9;

	// ��Я���Ĺ���������
	static const int toolBar = 27;

	// ��ǰѡ�еĹ�������
	int selectedIndex;

	// ������ʾ�����ľ��ο�͹���
	cocos2d::Sprite* bagBackground; // ������
	std::vector<cocos2d::Sprite*> toolIcons; // ����ͼ��

	static const int iconSize = 54; // ÿ��ͼ��Ŀ��/�߶�
	static const int spacing = 10; // ͼ����
};
#endif __BAG_H__