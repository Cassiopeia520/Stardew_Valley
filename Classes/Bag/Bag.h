#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"
#include "../Item/Item.h"

class Bag : public cocos2d::Node {
public:
	// ����ģʽ��ȡ����ʵ��
	static Bag* getInstance();

	// ��ʼ������
	bool init();

	// ��ӹ��ߵ�����
	bool addTool(Tool* tool);

	// �Ƴ�����
	void removeTool(const int index);

	// ��ȡĳ������
	Tool* getTool(const int index) const;

	// ����ѡ�еĹ���
	void selectTool(const int index);

	// ��ȡ��ǰѡ�еĹ���
	Tool* getSelectedTool() const;

	// ��ʾ����
	void updateDisplay();

	// ��ǰ��ӵ�еĹ���
	std::vector<Tool*> tools;

	//�򱳰��м�����Ʒ
	bool addItem(Item* item);

	// ��ȡ�����е���Ʒ
	const std::vector<Item*>& getItems() const;

private:
	// ����ʵ��
	static Bag* instance;

	std::vector<Item*> items;        // �����е���Ʒ

	// ˽�й��캯������ֹ���ʵ������ȷ��Ψһ��
	Bag();
	~Bag();

	// ��ֹ�����͸�ֵ
	Bag(const Bag&) = delete;
	Bag& operator=(const Bag&) = delete;

	// ��ǰѡ�еĹ�������
	int selectedIndex;

	// ������ʾ�����ľ��ο�͹���
	cocos2d::Sprite* bagBackground;			 // ������
	std::vector<cocos2d::Sprite*> toolIcons; // ����ͼ��

	static const int capacity = 9;			// �����Ź��ߵ�����
	static const int allCapacity = 9;		// ����������
	static const int iconSize = 54;			// ÿ��ͼ��Ŀ��/�߶�
	static const int spacing = 10;			// ͼ����
};
#endif __BAG_H__