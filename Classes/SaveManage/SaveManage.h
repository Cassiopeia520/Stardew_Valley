#ifndef __SAVE_MANAGE_H__
#define __SAVE_MANAGE_H__
#include <string>
#include <vector>
#include "cocos2d.h"

// ��������������ݵĽṹ
struct PlayerSaveData {
	float posX;
	float posY;
	float dirX;
	float dirY;
};

// ���������ͼλ�����ݵĽṹ
struct MapSaveData {
	float posX;
	float posY;
};

// �������汳����Ʒ���ݵĽṹ
struct BagItemData {
	int index;
	std::string itemName;
	int quantity;
};

// �������汳�����ݵĽṹ
struct BagSaveData {
	std::vector<BagItemData> items;
	int selectedIndex;
};

// ��������������Ҫ��������ݵĽṹ
struct SaveData {
	PlayerSaveData playerData;
	MapSaveData mapData;
	BagSaveData bagData;
};

// �洢������
class SaveManage {
public:
	// ��̬��������ȡ����ʵ��
	static SaveManage* getInstance();

	// �������ݵĹ��ýӿ�
	bool saveGameData();

	// �������ݵĹ��ýӿ�
	bool loadGameData();

private:
	// Ĭ�Ϲ��캯������������
	SaveManage() = default;
	~SaveManage() = default;
	
	// ���л��뷴���л�
	std::string SaveManage::serializeToJson(const SaveData& data);
	bool deserializeFromJson(const std::string& jsonStr, SaveData& data);

};

#endif