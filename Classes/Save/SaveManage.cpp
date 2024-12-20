/****************************************************************
 * File Function: ʵ�ִ浵�����࣬�û����˳������������¼��ش浵
 *				  ���Լ����������Ϣ�������е���Ʒ�͵�ͼ����Ϣ
 * Author:        ��׿��
 ****************************************************************/
#include "SaveManage.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Item/ItemFactory.h"

USING_NS_CC;

// ��ȡ����ʵ��
SaveManage* SaveManage::getInstance() {
	static SaveManage instance;
	return &instance;
}

// ���л� SaveData �� JSON �ַ���
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

	// �洢Bag����
	rapidjson::Value bagObj(rapidjson::kObjectType);
	rapidjson::Value itemsArray(rapidjson::kArrayType);
	for (const auto& bagItem : data.bagData.items) {
		rapidjson::Value itemObj(rapidjson::kObjectType);
		itemObj.AddMember("index", bagItem.index, alloc);
		itemObj.AddMember("itemName", rapidjson::Value(bagItem.itemName.c_str(), alloc).Move(), alloc);
		itemObj.AddMember("quantity", bagItem.quantity, alloc);
		itemsArray.PushBack(itemObj, alloc);
	}
	bagObj.AddMember("items", itemsArray, alloc);
	bagObj.AddMember("selectedIndex", data.bagData.selectedIndex, alloc);
	doc.AddMember("bagData", bagObj, alloc);

	// ���л�Ϊ�ַ���
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}

// �����л� JSON �ַ����� SaveData
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

	// ��ͼ����
	if (doc.HasMember("mapData") && doc["mapData"].IsObject()) {
		const rapidjson::Value& mapObj = doc["mapData"];
		if (mapObj.HasMember("posX") && mapObj["posX"].IsNumber()) {
			data.mapData.posX = mapObj["posX"].GetFloat();
		}
		if (mapObj.HasMember("posY") && mapObj["posY"].IsNumber()) {
			data.mapData.posY = mapObj["posY"].GetFloat();
		}
	}

	// Bag����
	if (doc.HasMember("bagData") && doc["bagData"].IsObject()) {
		const rapidjson::Value& bagObj = doc["bagData"];
		if (bagObj.HasMember("items") && bagObj["items"].IsArray()) {
			const rapidjson::Value& itemsArray = bagObj["items"];
			for (rapidjson::SizeType i = 0; i < itemsArray.Size(); i++) {
				const rapidjson::Value& itemObj = itemsArray[i];
				BagItemData bagItem;
				if (itemObj.HasMember("index") && itemObj["index"].IsInt()) {
					bagItem.index = itemObj["index"].GetInt();
				}
				if (itemObj.HasMember("itemName") && itemObj["itemName"].IsString()) {
					bagItem.itemName = itemObj["itemName"].GetString();
				}
				if (itemObj.HasMember("quantity") && itemObj["quantity"].IsInt()) {
					bagItem.quantity = itemObj["quantity"].GetInt();
				}
				data.bagData.items.push_back(bagItem);
			}
		}
		if (bagObj.HasMember("selectedIndex") && bagObj["selectedIndex"].IsInt()) {
			data.bagData.selectedIndex = bagObj["selectedIndex"].GetInt();
		}
	}

	return true;
}

// �������ݵĹ��ýӿ�
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

	// ��ȡBag����
	Bag* bag = Bag::getInstance();
	const auto& bagItems = bag->getItems();
	const auto& bagQuantities = bag->getQuantities();
	const int totalCapacity = bag->getTotalCapacity();
	for (int i = 0; i < totalCapacity; ++i) {
		Item* item = bag->getItem(i);
		if (item != nullptr) {
			BagItemData bagItem;
			bagItem.index = i;
			bagItem.itemName = item->getItemName();
			bagItem.quantity = bagQuantities[i];
			data.bagData.items.push_back(bagItem);
		}
	}
	data.bagData.selectedIndex = bag->getSelectedIndex();

	// ���л�
	std::string jsonStr = serializeToJson(data);
	std::string path = FileUtils::getInstance()->getDefaultResourceRootPath() + "../../savegame.json";

	return FileUtils::getInstance()->writeStringToFile(jsonStr, path);
}

// ������Ϸ����
bool SaveManage::loadGameData() {
	// ���Լ��ش浵����
	std::string path = FileUtils::getInstance()->getDefaultResourceRootPath() + "../../savegame.json";

	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
	SaveData data;

	bool success = deserializeFromJson(jsonStr, data);
	if (success) {
		// �ָ��������
		Player* player = Player::getInstance();
		player->setPosition(Vec2(data.playerData.posX, data.playerData.posY));
		player->setLastDirection(Vec2(data.playerData.dirX, data.playerData.dirY));
		
		// �ָ���ͼ����
		FarmMap* farmMap = FarmMap::getInstance();
		farmMap->setPosition(Vec2(data.mapData.posX, data.mapData.posY));

		// �ָ�Bag����
		Bag* bag = Bag::getInstance();
		bag->clearBag();
		for (const auto& bagItem : data.bagData.items) {
			// ʹ�ù����������� Item ʵ��
			Item* item = ItemFactory::createItem(bagItem.itemName);
			if (item != nullptr) {
				bag->setItem(bagItem.index, item, bagItem.quantity);
			}
		}
		// ����ѡ�е���Ʒ
		bag->setSelectedItem(data.bagData.selectedIndex);
		return true;
	}

	return false;
}