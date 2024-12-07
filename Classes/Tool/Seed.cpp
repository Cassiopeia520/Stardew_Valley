#include "Seed.h"
#include "cocos2d.h"

USING_NS_CC;

Seed* Seed::create() {
    Seed* seed = new (std::nothrow) Seed();
    if (seed && seed->init()) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

bool Seed::init() {
    // ���û���ĳ�ʼ������
    return Tool::init("seed");
}

void Seed::useItem() {
    return;
}