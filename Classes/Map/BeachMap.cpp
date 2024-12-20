/****************************************************************
 * File Function: ʵ�ֺ�̲��ͼ��
 * Author:        ��׿��
 ****************************************************************/
#include "BeachMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../Item/ItemFactory.h"
#include "../Npc/NoticeBoard.h"

USING_NS_CC;

// ��ʼ����̬ʵ��
BeachMap* BeachMap::instance = nullptr;

// ���캯��
BeachMap::BeachMap() : backgroundLayer(nullptr), waterLayer(nullptr) {}

// ��������
BeachMap::~BeachMap() {
    instance = nullptr;
}

// ��ȡ����ʵ��
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

// ��ʼ����ͼ
bool BeachMap::init(const std::string& tmxFile) {
    if (!SceneMap::init(tmxFile)) {
        return false;
    }
    
    // ��ȡ��ͼ�ĸ�����
    backgroundLayer = tiledMap->getLayer("Background");
    waterLayer = tiledMap->getLayer("Water");

    // ��λ��
    const Size mapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - mapSize.width / 2,  WINSIZE.height - mapSize.height);

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

    // �Ÿ�ʾ��
    NoticeBoard* board = NoticeBoard::create();
    board->setPosition(Vec2(BOARD_X, BOARD_Y));
    addChild(board);
    // ���lambda��������BeachMap����������ÿdtʱ�����һ��
    schedule([this](float dt) {

        // ���Ŀ��λ���Ƿ����ϰ���
        auto player = Player::getInstance();

        // ���ڵ�ͼ��������һ���ᵽ���λ��
        Vec2 playerSize2 = Vec2(0.0f, player->getContentSize().height * 1.0f);
        auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / MAP_MOVE_SPEED * 10.0f;
        if (isCollidable(playerPositionInMap)) {
            velocity = Vec2::ZERO;
            player->stopMoving();
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

// ��д�͵�ͼ����
void BeachMap::interactWithMap() {
}

// ��ͼ��ʱ�����
void BeachMap::mapUpdateByTime() {
}