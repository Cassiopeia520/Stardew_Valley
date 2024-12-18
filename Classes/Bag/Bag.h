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
	void setSelectedItem(const int index);

	// ��ȡ��ǰѡ�е���Ʒ
	Item* getSelectedItem() const;

	// ��ʾ����
	void updateDisplay();
	
	// ��ȡ������С��Ҳ���ǲ�ͬ��Ʒ�ĸ���
	int getSize();

	// ��ȡ��������Ʒ������
	int getItemIndex(const std::string& itemName);

	// ��ȡ��ǰѡ����Ʒ������
	int getSelectedIndex() {
		return selectedIndex;
	}

	// ��д�����Ա����getContentSize()
	const cocos2d::Size& getContentSize() const override;

	// ��ձ���
	void clearBag();

	//������Ʒ��ָ������
	void setItem(const int index, Item* item, const int quantity);

	// ��ȡ������
	int getTotalCapacity() const;

	// ��ȡ������Ʒ������
	const std::vector<Item*>& getItems() const;

	// ��ȡ������Ʒ������
	const std::vector<int>& getQuantities() const;

	// �鿴�������Ƿ���Ŀ����Ʒ
	bool checkItemIn(const std::string& targetName);
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

	// ������
	cocos2d::Sprite* bagBackground;

	// ��ǰ��ӵ�е���Ʒ
	std::vector<Item*> items;

	// ��Ʒ������ǩ
	std::vector<cocos2d::Label*> itemLabels;

	// ÿ����Ʒ������
	std::vector<int> quantities;

	// ��̬����
	static const int capacity = 9;			 // ��������Ʒ��һ������
	static const int row = 2;				 // 2��
	static const int iconSize = 54;			 // ÿ��ͼ��Ŀ��/�߶�
	static const int spacing = 10;			 // ͼ����
};
#endif __BAG_H__