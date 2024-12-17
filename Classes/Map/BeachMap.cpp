#include "BeachMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// ��ʼ����̬ʵ��
BeachMap* BeachMap::instance = nullptr;

TileNode* BeachMap::getTileNode(const int x, const int y) const {
    return mapTileNode[x][y];
}

BeachMap::~BeachMap() {
    instance = nullptr;
}

BeachMap::BeachMap() : velocity(Vec2::ZERO) {}

BeachMap* BeachMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) BeachMap();
        if (instance && instance->init("Maps/beach/beachMap.tmx")) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool BeachMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    velocity = Vec2::ZERO;

    // ����������ļ���,���ص�ͼ
    if (!tmxFile.empty()) {
        tiledMap = TMXTiledMap::create(tmxFile);
        if (!tiledMap) {
            return false;
        }
    }
    addChild(tiledMap);

    const Size beachMapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - beachMapSize.width / 2, WINSIZE.height / 2 - beachMapSize.height / 2);

    backgroundLayer = tiledMap->getLayer("Background");
    waterLayer = tiledMap->getLayer("Water");

    // ��ȡ�ߵ��ͼ�ĳ���
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // ����ͼ��Ϊÿһ��ͼ��
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Water(Vec2(x, y));
            }
            else if (backgroundLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Soil(Vec2(x, y));
            }

        }
    }
    // ���lambda��������BeachMap����������ÿdtʱ�����һ��
    schedule([this](float dt) {

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
        position.x = std::max(WINSIZE.width - getMapSize().width, std::min(position.x, 0.0f));
        position.y = std::max(WINSIZE.height - getMapSize().height, std::min(position.y, 0.0f));

        setPosition(position);
        }, "beach_map");
    return true;
}

void BeachMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

const Size& BeachMap::getMapSize() const {
    return tiledMap->getContentSize();
}


// ��ײ��⣺������λ���Ƿ����ϰ���, positon�������ڵ�ͼ����ϵ��ԭ�������½ǣ��е�����
bool BeachMap::isCollidable(const Vec2& position) const {
    // ��ȡ��ͼ����Ƭ��С
    const Size tileSize = tiledMap->getTileSize();
    const Size mapSize = tiledMap->getMapSize();

    // �������ڵ�ͼ�е�����ת��Ϊ��Ƭ��ͼ���꣨ԭ�������Ͻǣ�
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    // ����Ƿ��ڵ�ͼ��Χ��
    if (x < 0 || x >= mapSize.width || y < 0 || y >= mapSize.height) {
        return true; // ������ͼ��Χ��Ϊ�ϰ���
    }

    // ��ײ���
    TileType tileType = mapTileNode[x][y]->getTileType();
    if (tileType == TileType::Water) {
        return true;
    }
    else {
        return false;
    }
}

void BeachMap::interactWithBeachMap() {
    //// ��ȡ��ҡ���ͼ������ʵ��
    //Player* player = Player::getInstance();
    //BeachMap* beachMap = BeachMap::getInstance();
    //Bag* bag = Bag::getInstance();

    //if (!player->getUseItemEnable()) {
    //    return;
    //}

    //// ��ȡҪ����������λ��
    //Vec2 playerPosition = player->getPosition();
    //const Size tileSize = beachMap->tiledMap->getTileSize();
    //const Size mapSize = beachMap->tiledMap->getMapSize();
    //playerPosition = playerPosition - beachMap->getPosition();
    //playerPosition.y = playerPosition.y - player->getContentSize().height / 2 + 10.0f;
    //playerPosition.x = playerPosition.x / tileSize.width;
    //playerPosition.y = (mapSize.height * tileSize.height - playerPosition.y) / tileSize.height;
    //const Vec2 lastDirection = player->getLastDirection();

    //// ��ǰ����ǰ����ߵ�
    //if (lastDirection == Vec2(1, 0) && playerPosition.x + 1 < mapSize.width - 1) {
    //    playerPosition.x++;
    //}
    //else if (lastDirection == Vec2(0, 1) && playerPosition.y - 1 >= 0) {
    //    playerPosition.y--;
    //}
    //else if (lastDirection == Vec2(-1, 0) && playerPosition.x - 1 >= 0) {
    //    playerPosition.x--;
    //}
    //else if (lastDirection == Vec2(0, -1) && playerPosition.y + 1 < mapSize.height - 1) {
    //    playerPosition.y++;
    //}

    //const int x = playerPosition.x;
    //const int y = playerPosition.y;

    //// ��õ�ǰ������ʹ�õĹ���
    //std::string currentItemName = player->getCurrentItemName();
}

void BeachMap::stopMoving() {
    velocity = Vec2::ZERO;
}

TMXTiledMap* BeachMap::getTiledMap() {
    return tiledMap;
}