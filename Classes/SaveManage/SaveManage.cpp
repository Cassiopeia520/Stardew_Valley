#include "SaveManage.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"

USING_NS_CC;

const std::string SaveManage::SAVE_FILE_NAME = "playerSave.json";

// ��ȡ����ʵ��
SaveManage* SaveManage::getInstance() {
	static SaveManage instance;
	return &instance;
}

// ���л���json�ļ�
std::string SaveManage::serializeToJson(const SaveData& data) {
	rapidjson::Document doc;
	doc.SetObject();
	auto& alloc = doc.GetAllocator();

	// �洢���λ�úͳ���
	rapidjson::Value playerObj(rapidjson::kObjectType);
	playerObj.AddMember("posX", data.playerData.posX, alloc);
	playerObj.AddMember("posY", data.playerData.posY, alloc);
	playerObj.AddMember("dirX", data.playerData.dirX, alloc);
	playerObj.AddMember("dirY", data.playerData.dirY, alloc);
	doc.AddMember("playerData", playerObj, alloc);

	// �洢��ͼ��λ��
	rapidjson::Value mapObj(rapidjson::kObjectType);
	mapObj.AddMember("posX", data.mapData.posX, alloc);
	mapObj.AddMember("posY", data.mapData.posY, alloc);
	doc.AddMember("mapData", mapObj, alloc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}


// ��json�ļ��з����л�
bool SaveManage::deserializeFromJson(const std::string& jsonStr, SaveData& data) {
	rapidjson::Document doc;
	if (doc.Parse(jsonStr.c_str()).HasParseError()) {
		return false;
	}
	if (!doc.IsObject()) {
		return false;
	}
	// �������
	if (doc.HasMember("playerData") && doc["playerData"].IsObject()) {
		const rapidjson::Value& playerObj = doc["playerData"];
		if (playerObj.HasMember("posX") && playerObj["posX"].IsNumber()) {
			data.playerData.posX = playerObj["posX"].GetFloat();
		}
		if (playerObj.HasMember("posY") && playerObj["posY"].IsNumber()) {
			data.playerData.posY = playerObj["posY"].GetFloat();
		}
		if (playerObj.HasMember("dirX") && playerObj["dirX"].IsNumber()) {
			data.playerData.dirX = playerObj["dirX"].GetFloat();
		}
		if (playerObj.HasMember("dirY") && playerObj["dirY"].IsNumber()) {
			data.playerData.dirY = playerObj["dirY"].GetFloat();
		}
	}
	if (doc.HasMember("mapData") && doc["mapData"].IsObject()) {
		const rapidjson::Value& mapObj = doc["mapData"];
		if (mapObj.HasMember("posX") && mapObj["posX"].IsNumber()) {
			data.mapData.posX = mapObj["posX"].GetFloat();
		}
		if (mapObj.HasMember("posY") && mapObj["posY"].IsNumber()) {
			data.mapData.posY = mapObj["posY"].GetFloat();
		}
	}


	return true;
}

bool SaveManage::saveGameData() {
	SaveData data;

	// ��ȡ�������
	const Player* player = Player::getInstance();
	data.playerData.posX = player->getPositionX();
	data.playerData.posY = player->getPositionY();
	data.playerData.dirX = player->getLastDirection().x;
	data.playerData.dirY = player->getLastDirection().y;
	
	// ��ȡ��ͼ����
	const FarmMap* farmMap = FarmMap::getInstance();
	data.mapData.posX = farmMap->getPositionX();
	data.mapData.posY = farmMap->getPositionY();

	// ���л�
	std::string jsonStr = serializeToJson(data);
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;

	return FileUtils::getInstance()->writeStringToFile(jsonStr, path);
}


bool SaveManage::loadGameData() {
	// ���Լ��ش浵����
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;

	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
	SaveData data;

	bool success = deserializeFromJson(jsonStr, data);
	if (success) {
		Player* player = Player::getInstance();
		player->setPosition(Vec2(data.playerData.posX, data.playerData.posY));
		player->setLastDirection(Vec2(data.playerData.dirX, data.playerData.dirY));
		
		FarmMap* farmMap = FarmMap::getInstance();
		farmMap->setPosition(Vec2(data.mapData.posX, data.mapData.posY));
		return true;
	}

	return false;
}