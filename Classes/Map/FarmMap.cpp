#include "FarmMap.h"
#include "../Player/Player.h"

USING_NS_CC;

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
        obstacleLayer = map->getLayer("obstacles");
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

            auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / 200.0f * 10.0f;
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
    velocity = direction * 200.f;
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
    int tileGID = obstacleLayer->getTileGIDAt(Vec2(x, y));
    if (tileGID != 0) {
        return true;
    }
    else {
        return false;
    }
}

