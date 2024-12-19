#include "ForestMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../Item/ItemFactory.h"
#include "../Npc/NoticeBoard.h"

USING_NS_CC;

// ��ʼ����̬ʵ��
ForestMap* ForestMap::instance = nullptr;

// ���캯��
ForestMap::ForestMap() : backgroundLayer(nullptr) {}

// ��������
ForestMap::~ForestMap() {
    instance = nullptr;
}

// ��ȡ����ʵ��
ForestMap* ForestMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) ForestMap();
        if (instance && instance->init("Maps/forest/forest.tmx")) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// ��ʼ����ͼ
bool ForestMap::init(const std::string& tmxFile) {
    if (!SceneMap::init(tmxFile)) {
        return false;
    }

    // ��ȡ��ͼ�ĸ�����
    backgroundLayer = tiledMap->getLayer("Background");

    // ��λ��
    const Size mapSize = getMapSize();
    setPosition(0.0f, WINSIZE.height / 2 - mapSize.height / 2);

    // ��ȡ�ߵ��ͼ�ĳ���
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // ����ͼ��Ϊÿһ��ͼ��
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (backgroundLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Soil(Vec2(x, y));
            }
        }
    }

    // �Ÿ�ʾ��
    NoticeBoard* board = NoticeBoard::create();
    board->setPosition(Vec2(BOARD_X, BOARD_Y));
    addChild(board);
    // ���lambda��������ForestMap����������ÿdtʱ�����һ��
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
        }, "forest_map");
    return true;
}

void ForestMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

// ��ײ��⣺������λ���Ƿ����ϰ���, position�������ڵ�ͼ����ϵ��ԭ�������½ǣ��е�����
bool ForestMap::isCollidable(const Vec2& position) const {
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
void ForestMap::interactWithMap() {
}

// ��ͼ��ʱ�����
void ForestMap::mapUpdateByTime() {
}
