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

struct SaveData {
	PlayerSaveData playerData;
	MapSaveData mapData;	
};

class SaveManage {
public:
	static SaveManage* getInstance();

	// �������ݵĹ��ýӿ�
	bool saveGameData();

	// �������ݵĹ��ýӿ�
	bool loadGameData();

private:
	SaveManage() = default;
	~SaveManage() = default;
	
	std::string SaveManage::serializeToJson(const SaveData& data);

	bool deserializeFromJson(const std::string& jsonStr, SaveData& data);

	static const std::string SAVE_FILE_NAME; // "player_save.json"
};

#endif

