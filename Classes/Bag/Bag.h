#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"
#include "../Food/Food.h"

class Bag : public cocos2d::Node {
public:
	// ����ģʽ��ȡ����ʵ��
	static Bag* getInstance();

	// ��ʼ������
	bool init();

	// �����Ʒ������
	bool addItem(Item* item);
		
	// �Ƴ���Ʒ
	void removeItem(const int index);

	// ��ȡĳ����Ʒ
	Item* getItem(const int index) const;

	// ����ѡ�е���Ʒ
	void selectItem(const int index);

	// ��ȡ��ǰѡ�е���Ʒ
	Item* getSelectedItem() const;

	// ��ʾ����
	void updateDisplay();

	// ��ǰ��ӵ�е���Ʒ
	std::vector<Item*> items;


private:
	// ����ʵ��
	static Bag* instance;

	// ˽�й��캯������ֹ���ʵ������ȷ��Ψһ��
	Bag();
	~Bag();

	// ��ֹ�����͸�ֵ
	Bag(const Bag&) = delete;
	Bag& operator=(const Bag&) = delete;

	// ��ǰѡ�е���Ʒ����
	int selectedIndex;

	// ������ʾ�����ľ��ο����Ʒ
	cocos2d::Sprite* bagBackground;			 // ������
	std::vector<cocos2d::Sprite*> itemIcons; // ��Ʒͼ��

	static const int capacity = 9;			// ��������Ʒ������
	static const int allCapacity = 9;		// ����������
	static const int iconSize = 54;			// ÿ��ͼ��Ŀ��/�߶�
	static const int spacing = 10;			// ͼ����
};
#endif __BAG_H__