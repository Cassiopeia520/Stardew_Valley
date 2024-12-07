#include "FarmMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include<string>

USING_NS_CC;

// ��ʼ����̬ʵ��
FarmMap* FarmMap::instance = nullptr;

TileNode* FarmMap::getTileNode(int x, int y)
{
    return mapTileNode[x][y];
}

FarmMap::FarmMap() : velocity(Vec2::ZERO) {}

FarmMap::~FarmMap() {
    instance = nullptr;
}

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

        // ��ȡ��ͼ�ĸ���ͼ��
        grassLayer = map->getLayer("Grass");
        soilLayer = map->getLayer("Soil");
        obstacleLayer = map->getLayer("Obstacles");
        moldLayer = map->getLayer("Mold");
        waterLayer = map->getLayer("Water");
        stoneLayer = map->getLayer("Stone");

        // ��ȡ�ߵ��ͼ�ĳ���
        int width = map->getMapSize().width;
        int height = map->getMapSize().height;
        
        // ����ͼ��Ϊÿһ��ͼ��
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (stoneLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Stone(Vec2(x,y));
                }
                else if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Water(Vec2(x,y));
                }
                else if (moldLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Mold(Vec2(x,y));
                }
                else if(obstacleLayer->getTileGIDAt(Vec2(x,y))){
                    mapTileNode[x][y] = new Obstacle(Vec2(x, y));
                }
                else if (soilLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Soil(Vec2(x, y));
                }
                else {
                    int GID = grassLayer->getTileGIDAt(Vec2(x, y));
                    mapTileNode[x][y] = new Grass(Vec2(x, y),GID);
                }
            }
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
    npc->setPosition(position);
    this->addChild(npc, 5);

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

    // ��ײ���
    TileType tileType = mapTileNode[x][y]->getTileType();
    if (tileType == TileType::Stone || tileType == TileType::Obstacle || tileType == TileType::Water||tileType == TileType::Mold) {
        return true;
    }
    else {
        return false;
    }
}

// �����ũ���Ľӿ�
void FarmMap::interactWithFarmMap() {
    // ��ȡ��ҡ���ͼ������ʵ��
    Player* player = Player::getInstance();
    FarmMap* farmMap = FarmMap::getInstance();
    Bag* bag = Bag::getInstance();

    // ��ȡҪ����������λ��
    Vec2 playerPosition = player->getPosition();
    const Size tileSize = farmMap->map->getTileSize();
    const Size mapSize = farmMap->map->getMapSize();
    playerPosition = playerPosition - farmMap->getPosition();
    playerPosition.y = playerPosition.y - player->getContentSize().height / 2 + 10.0f;
    int x = playerPosition.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - playerPosition.y) / tileSize.height;
    Vec2 lastDirection = player->getLastDirection();

    if (lastDirection == Vec2(1, 0) && x + 1 < mapSize.width - 1) {
        x++;
    }
    else if (lastDirection == Vec2(0, 1) && y - 1 >= 0) {
        y--;
    }
    else if (lastDirection == Vec2(-1, 0) && x - 1 >= 0) {
        x--;
    }
    else if (lastDirection == Vec2(0, -1) && y + 1 < mapSize.height - 1) {
        y++;
    }

    // �����Ҫ������λ��
    Vec2 interactPosition = Vec2(x, y);

    // ��õ�ǰ������ʹ�õĹ���
    std::string currentTool = player->getCurrentItemName();

    // ���ͼ��Ľ���
    if (currentTool == "pickaxe" && mapTileNode[x][y]->getTileType() == TileType::Stone) {      // ��ǰ��ʯͷ��
        dynamic_cast<Stone*>(mapTileNode[x][y])->knockRock();                                   // �û�һ��ʯͷ
        if (dynamic_cast<Stone*>(mapTileNode[x][y])->isBroken() == true) {                      // �ж�ʯͷ�Ƿ����
            delete mapTileNode[x][y];
            mapTileNode[x][y] = nullptr;
            mapTileNode[x][y] = new Soil(Vec2(x, y)); 
            stoneLayer->setTileGID(0, Vec2(x, y));
            soilLayer->setTileGID(mapTileNode[x][y]->getCurrentGID(), Vec2(x, y));
        }
    }
    else if (currentTool == "wateringcan" && mapTileNode[x][y]->getTileType() == TileType::Water) {  // ��ǰ��������ˮ��
        int wateringCanIndex = bag->getToolIndex("wateringcan");
        int waterShortageAmount = MAX_WATERINGCAN_CAPACITY - dynamic_cast<Kettle*>(bag->items[wateringCanIndex])->getCurrentWaterLevel();
        if (waterShortageAmount <= dynamic_cast<Water*>(mapTileNode[x][y])->getCurrentWaterResource()) {

        }
    }



    // ���ͼ��Ľ���
    mapTileNode[x][y]->interact(currentTool);

    // ����ͼ��
    soilLayer->setTileGID(mapTileNode[x][y]->getCurrentGID(), Vec2(x, y));
}

void FarmMap::stopMoving() {
    velocity = Vec2::ZERO;
}

// ��ͼ��ʱ��ĸ���
void FarmMap::farmMapUpdateByTime() {
    
    // �������������ʱ�������
    for (int x = 0; x < FARMMAP_WIDTH; x++) {
        for (int y = 0; y < FARMMAP_HEIGHT; y++) {
            if (mapTileNode[x][y]->getTileType() == TileType::Soil) {
                mapTileNode[x][y]->updateByTime();
                soilLayer->setTileGID(mapTileNode[x][y]->getCurrentGID(),Vec2(x,y));
                //CCLOG("%d", mapTileNode[x][y]->getCurrentGID());
            }
        }
    }
}