/****************************************************************
 * File Function: ʵ�����е�ͼ�Ļ���
 * Author:        ��׿��
 ****************************************************************/
#include "SceneMap.h"

USING_NS_CC;

// ���캯��
SceneMap::SceneMap() : velocity(Vec2::ZERO), tiledMap(nullptr) {}

// ��������
SceneMap::~SceneMap() {
    // ���� mapTileNode
    for (auto& row : mapTileNode) {
        for (auto& tile : row) {
            if (tile) {
                delete tile;
                tile = nullptr;
            }
        }
    }
}

// ���� TMX ��ͼ
bool SceneMap::loadMap(const std::string& tmxFile) {
    if (tmxFile.empty()) {
        return false;
    }

    tiledMap = TMXTiledMap::create(tmxFile);
    if (!tiledMap) {
        CCLOG("Failed to load TMX file: %s", tmxFile.c_str());
        return false;
    }

    addChild(tiledMap);
    return true;
}

// ��ʼ����ͼ
bool SceneMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    // ���ص�ͼ
    if (!loadMap(tmxFile)) {
        return false;
    }

    // ���õ�ͼλ��Ϊ��Ļ����
    const Size mapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - mapSize.width / 2, WINSIZE.height / 2 - mapSize.height / 2);

    // ��ȡ���в㲢�洢
    auto allLayers = tiledMap->getChildren();
    for (auto& layer : allLayers) {
        auto tmxLayer = dynamic_cast<TMXLayer*>(layer);
        if (tmxLayer) {
            layers.push_back(tmxLayer);
        }
    }

    // ��ȡ��ͼ�ĳ���
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // ��ʼ�� mapTileNode
    mapTileNode.resize(width, std::vector<TileNode*>(height, nullptr));

    return true;
}

// ���µ�ͼλ��
void SceneMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction;
}

// ��ȡ��ͼ��С
const Size& SceneMap::getMapSize() const {
    return tiledMap->getContentSize();
}

// ��ײ���
bool SceneMap::isCollidable(const Vec2& position) const {
    // Ĭ��ʵ�֣����������д
    return false;
}

// ���ͼ����
void SceneMap::interactWithMap() {
    // Ĭ��ʵ�֣����������д
}

// ֹͣ��ͼ�ƶ�
void SceneMap::stopMoving() {
    velocity = Vec2::ZERO;
}

// ��ȡ TMX ��Ƭ��ͼ����
TMXTiledMap* SceneMap::getTiledMap() {
    return tiledMap;
}

// ��ȡ�ض�λ�õ� TileNode
TileNode* SceneMap::getTileNode(const int x, const int y) const {
    if (x < 0 || y < 0 || x >= static_cast<int>(mapTileNode.size()) || y >= static_cast<int>(mapTileNode[0].size())) {
        return nullptr;
    }
    return mapTileNode[x][y];
}

// ��ͼ��ʱ�����
void SceneMap::mapUpdateByTime() {
    // Ĭ��ʵ�֣����������д
}