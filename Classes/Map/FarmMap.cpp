#include "FarmMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
USING_NS_CC;

// ������ĸ���
void Soil::till() {
    isTilled = true;
    soilStage = SoilStage::TILLED;
}

// ���������λ��
Vec2 Soil::getPosition() {
    return position;
}

// �жϸ������Ƿ�ɸ���
bool Soil::isTillable() {
    return isTilled == false && entity == nullptr;
}

// �жϸ������Ƿ����ֲ
bool Soil::isPlantable() {
    return isTilled == true && entity == nullptr;
}

// ��ʼ����̬ʵ��
FarmMap* FarmMap::instance = nullptr;

FarmMap::FarmMap() : velocity(Vec2::ZERO) {}

FarmMap::~FarmMap() {}

FarmMap* FarmMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) FarmMap();
        if (instance) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool FarmMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    velocity = Vec2::ZERO;

    // ����������ļ���,���ص�ͼ
    if (!tmxFile.empty()) {
        map = TMXTiledMap::create(tmxFile);
        if (!map) {
            return false;
        }
        this->addChild(map);

        // ��ȡ�ϰ����
        grassLayer = map->getLayer("Grass");
        soilLayer = map->getLayer("Soil");
        obstacleLayer = map->getLayer("obstacles");
        stoneLayer = map->getLayer("stone");
        waterLayer = map->getLayer("water");

        int width = map->getMapSize().width;
        int height = map->getMapSize().height;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::WATER);
                }
                else if (stoneLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::STONE);
                }
                else if (obstacleLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::HOUSE);
                }
                else if (soilLayer->getTileGIDAt(Vec2(x, y))) {
                    auto soilInMap = new Soil(Vec2(x, y));
                    soil.push_back(soilInMap);
                }
                else {
                    //mapTiles[x][y] = TileNode(TileType::GRASS);
                }
                //mapTiles[x][y].position = Vec2(x, y);
                
            }
        }
        
        //CCLOG("successful map");

        if (!obstacleLayer) {
            CCLOG("No 'obstacles' layer found in TMX file.");
            return false;
        }

        // ���lambda��������FarmMap����������ÿdtʱ�����һ��
        schedule([this](float dt) {
            // ��ȡ����ߴ�
            const auto visibleSize = Director::getInstance()->getVisibleSize();

            // ���Ŀ��λ���Ƿ����ϰ���
            auto player = Player::getInstance();

            // ���ڵ�ͼ��������һ���ᵽ���λ��
            // �����- velocity / 200.0f * 10.0f��Ԥ����һ����λ��
            // velocity / 200.0f����Ϊvelocity�ľ���ֵ��200
            Vec2 playerSize2 = Vec2(0.0f, player->getContentSize().height * 1.0f);

            auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / MAP_MOVE_SPEED * 10.0f;
            if (isCollidable(playerPositionInMap)) {
                velocity = Vec2::ZERO;
            }
            auto position = getPosition() + velocity * dt;
            // max��֤���ڵ����½磬 min��֤С�ڵ����Ͻ�
            position.x = std::max(visibleSize.width - getMapSize().width, std::min(position.x, 0.0f));
            position.y = std::max(visibleSize.height - getMapSize().height, std::min(position.y, 0.0f));

            setPosition(position);
            }, "farm_map");
    }

    return true;
}

bool FarmMap::npcInit(const Vec2& position, Npc* npc)
{
    npc->sprite->setPosition(position);
    this->addChild(npc->sprite, 5);

    return true;
}

void FarmMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

Size FarmMap::getMapSize() const {
    return map->getContentSize();
}

// ��ײ��⣺������λ���Ƿ����ϰ���, positon�������ڵ�ͼ����ϵ��ԭ�������½ǣ��е�����
bool FarmMap::isCollidable(const Vec2& position) const {
    if (!obstacleLayer) {
        return false;
    }

    // ��ȡ��ͼ����Ƭ��С
    const Size tileSize = map->getTileSize();
    const Size mapSize = map->getMapSize();

    // �������ڵ�ͼ�е�����ת��Ϊ��Ƭ��ͼ���꣨ԭ�������Ͻǣ�
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    // ����Ƿ��ڵ�ͼ��Χ��
    if (x < 0 || x >= mapSize.width || y < 0 || y >= mapSize.height) {
        return true; // ������ͼ��Χ��Ϊ�ϰ���
    }

    // ��ȡ�ϰ�����Ƭ�� GID����Ƭ ID��
    int tileGIDInObstacle = obstacleLayer->getTileGIDAt(Vec2(x, y));
    int tileGIDInStone = stoneLayer->getTileGIDAt(Vec2(x, y));
    int tileGIDInWater = waterLayer->getTileGIDAt(Vec2(x, y));
    if (tileGIDInObstacle||tileGIDInStone||tileGIDInWater) {
        return true;
    }
    else {
        return false;
    }
 
}

void FarmMap::replaceTile(const Vec2& position, int GID) {
    soilLayer->setTileGID(8, position);
}

// �����ũ���Ľ�������
void FarmMap::interactWithFarmMap(Vec2 position) {
    if (soilLayer->getTileGIDAt(position)){
        soilLayer->setTileGID(8, position);
    }
}