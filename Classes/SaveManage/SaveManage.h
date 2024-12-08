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

class SaveManage {
public:
	static SaveManage* getInstance();

	// ����������ݵ��ļ�
	bool savePlayerData(const PlayerSaveData& data);

	// ������м����������
	bool loadPlayerData(PlayerSaveData& data);

private:
	SaveManage() = default;
	~SaveManage() = default;
	
	std::string serializeToJson(const PlayerSaveData& data);

	bool deserializeFromJson(const std::string& jsonStr, PlayerSaveData& data);

	static const std::string SAVE_FILE_NAME; // "player_save.json"
};

#endif

