#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Npc/Npc.h"
#include "Entity.h"
#include "../Festival/Festival.h"
#include <string>
#include <memory>
#include <vector>

enum class TileType {
	SOIL,
	GRASS,
	PLOWEDSOIL,
	WATEREDSOIL,
	CROP,
	HOUSE,
	STONE,
	WATER,
};

enum class SoilStage {
	ROW,
	TILLED,
	WATERED,
	PLANTED,
};

// ������
class Soil {
public:
	// ������Ĺ��캯��
	Soil(Vec2 position) :
		isTilled(false), isFertilized(false), isWatered(false),
		isDry(false), isDiseased(false), position(position),
		entity(nullptr),soilStage(SoilStage::ROW),isPlanted(false){}

	// ��������
	void till();

	// ��øõؿ�λ��
	Vec2 getPosition();

	// �Ƿ�ɳ���
	bool isTillable();

	// �жϸõ��Ƿ����ֲ
	bool isPlantable();
	// ��ˮ
	//void water();
	// ʩ��
	//void fertilize();
	// ��ֲ����
	//void plantCrop(const std::string& type, int maturityDays); 
	// ���𲡺�
	//void applyPesticide();       
	// ÿ�ո�������״̬
	//void updateSoil();       
	// �ջ�����
	//void harvestCrop();                       
private:
	// ��ǰ���ص�״̬
	SoilStage soilStage;
	// �Ƿ񱻳���
	bool isTilled;
	// �Ƿ���ֲ
	bool isPlanted;
	bool isFertilized;
	bool isWatered;
	bool isDry;
	bool isDiseased;
	// ��¼��ǰλ��
	Vec2 position;
	Entity* entity;
};

// �ݵ��� ����
class Grass {
public:   
	// �ж��Ƿ��ж���
	bool hasAnimal() const;

	// ��ȡ��ǰ����
	Entity* getAnimal() const;

	// ��Ӷ��ﵽ�ݵ�
	bool addAnimal(Entity* newEntity) {
		if (!entity) {
			entity = newEntity;
			return true;
		}
		return false; // �ݵ��Ѿ��ж���
	}

	// �Ƴ��ݵ��ϵĶ���
	void removeAnimal() {
		entity = nullptr;
	}

private:
	// ��¼��ǰ��Ƭλ�õĶ���
	Entity* entity;
	// ��¼��ǰ��Ƭ��λ��
	Vec2 position;
};

// ũ����ͼ��
class FarmMap : public cocos2d::Node {
public:
	// ��ȡ����ʵ��
	static FarmMap* getInstance();

	// ��ʼ����ͼ
	bool init(const std::string& tmxFile);

	std::vector<Festival*> festivals;

	//���ͼ����npc
	bool npcInit(const Vec2& position, Npc* npc);

	// ���µ�ͼλ��
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// ��ȡ��ͼ��С
	cocos2d::Size getMapSize() const;

	// ��ײ��⣺������λ���Ƿ����ϰ���
	bool isCollidable(const cocos2d::Vec2& position) const;

	// ������������ũ���Ľ����߼�
	void interactWithFarmMap(Vec2 position);

	// ��Ƭ��ͼ����
	cocos2d::TMXTiledMap* map;

	// �洢��Ƭ������
	//std::vector<std::vector<std::unique_ptr<TileNode>>> mapTiles;

	// ����Ƭ�滻�ɲ�ͬ����
	void replaceTile(const Vec2& position,int GID);

	cocos2d::TMXLayer* grassLayer;
	cocos2d::TMXLayer* obstacleLayer;
	cocos2d::TMXLayer* stoneLayer;
	cocos2d::TMXLayer* soilLayer;
	cocos2d::TMXLayer* waterLayer;

	// �����洢��ͬͼ���ϵ���
	std::vector<Soil*> soil;
 
private:
	// ���캯������������˽�л�
	FarmMap();
	~FarmMap();

	// ���ÿ�������͸�ֵ����
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// ��ͼ��ǰ��ƫ��λ��
	cocos2d::Vec2 currentPosition;

	// ��ͼ��ƫ���ٶ�
	cocos2d::Vec2 velocity;

	// ����ʵ��
	static FarmMap* instance;

	// �洢��Ƭ������
	//std::vector<std::vector<TileNode>> mapTiles;


};

#endif