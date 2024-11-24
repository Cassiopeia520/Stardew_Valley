#include "Player.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

// �����Ƕ��� problemLoading ����
static void problemLoading(const char* filename) {
	CCLOG("Error while loading: %s", filename);
	printf("Error while loading: %s\n", filename);
}

// ��ʼ����̬��Ա����
Player* Player::instance = nullptr;

Player::Player()
	: velocity(Vec2::ZERO),
	name(""),
	currentAnimationName(""),
	lastDirection(Vec2::ZERO) {
}

Player::~Player() {}

Player* Player::getInstance() {
	if (instance == nullptr) {
		instance = new (std::nothrow) Player();
		if (instance && instance->init()) {
			instance->autorelease();
		}
		else {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

bool Player::init() {
	if (!Sprite::initWithFile("player_walk_images/stand_down.png")) {
		problemLoading("player_walk_images/stand_down.png");
		return false;
	}

	// ��ʼ�ٶ�Ϊ��
	velocity = Vec2::ZERO;
	loadAnimations();
	// ÿdtʱ�����һ��
	schedule([this](float dt) {
			// ��ȡ����ߴ����ҳߴ�
			const auto visibleSize = Director::getInstance()->getVisibleSize();

			const Vec2 playerSize(Player::getInstance()->getContentSize());

			auto position = getPosition() + velocity * dt;
			// �߽��⣬��ֹ����Ƴ���Ļ
			position.x = std::max(playerSize.x / 2, std::min(position.x, visibleSize.width - playerSize.x / 2));
			position.y = std::max(playerSize.y / 2, std::min(position.y, visibleSize.height - playerSize.y / 2));
			setPosition(position);
		}, "player_movement");

	return true;
}

void Player::playAnimation(const std::string& animationName) {
    CCLOG("Play animation: %s", animationName.c_str());

    if (currentAnimationName == animationName) {
        CCLOG("Already playing animation %s", animationName.c_str());
        return; // �����ǰ�Ѿ��ڲ�����ͬ�Ķ������������ظ�����
    }

    stopAllActions(); // ֹͣ���ж���

    if (animations.find(animationName) != animations.end()) {
        auto animate = animations[animationName];

        if (animate) {
            // ȷ�� animate �� Animate ���͵Ķ���
            if (dynamic_cast<cocos2d::Animate*>(animate)) {
                auto sequence = cocos2d::Sequence::create(
                    animate,
                    nullptr
                );

                auto repeatForever = cocos2d::RepeatForever::create(sequence);
                runAction(repeatForever);
                currentAnimationName = animationName;
                CCLOG("Playing animation %s", animationName.c_str());
            }
            else {
                CCLOG("Error: animate object is not of type Animate for %s", animationName.c_str());
            }
        }
        else {
            CCLOG("Animate object is null for %s", animationName.c_str());
        }
    }
    else {
        CCLOG("Error: Animation for %s not found!", animationName.c_str());
    }
}

void Player::moveByDirection(const Vec2& direction) {
    CCLOG("Move by direction: (%f, %f)", direction.x, direction.y);
    if (direction.lengthSquared() == 0) {
        CCLOG("No movement detected.");
        return;
    }
    velocity = direction * 200.0f;
    //loadAnimations();

    if (direction.x > 0) {
        playAnimation("walk_right");
        createWalkFrames("right/", "walk_right", 3);
        lastDirection = Vec2(1, 0); // ��¼����ƶ��ķ���
    }
    else if (direction.x < 0) {
        playAnimation("walk_left");
        createWalkFrames("left/", "walk_left", 3);
        lastDirection = Vec2(-1, 0); // ��¼����ƶ��ķ���
    }
    else if (direction.y > 0) {
        playAnimation("walk_up");
        createWalkFrames("up/", "walk_up", 4);

        lastDirection = Vec2(0, 1); // ��¼����ƶ��ķ���
    }
    else if (direction.y < 0) {
        playAnimation("walk_down");
        createWalkFrames("down/", "walk_down", 4);
        lastDirection = Vec2(0, -1); // ��¼����ƶ��ķ���
    }
}

void Player::stopMoving() {
    CCLOG("Stop moving");
    velocity = Vec2::ZERO; // ֹͣ�ƶ�
    stopAllActions();

    // ��������ƶ��ķ�������վ������
    if (lastDirection.equals(Vec2(1, 0))) {
        setStandPose("stand_right");
    }
    else if (lastDirection.equals(Vec2(-1, 0))) {
        setStandPose("stand_left");
    }
    else if (lastDirection.equals(Vec2(0, 1))) {
        setStandPose("stand_up");
    }
    else if (lastDirection.equals(Vec2(0, -1))) {
        setStandPose("stand_down");
    }
}

void Player::setPlayerName(const std::string& name) {
    this->name = name;
}

std::string Player::getPlayerName() const {
    return name;
}

void Player::loadAnimations() {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

    // ����վ��֡������
    createStandFrame("player_walk_images/stand_down.png", "stand_down");
    createStandFrame("player_walk_images/stand_up.png", "stand_up");
    createStandFrame("player_walk_images/stand_left.png", "stand_left");
    createStandFrame("player_walk_images/stand_right.png", "stand_right");

}

void Player::createWalkFrames(const std::string& baseFilename, const std::string& animationName, int frameCount) {
    SpriteFrame* frame = nullptr;

    Vector<SpriteFrame*> frameVec;

    for (int i = 0; i < frameCount; ++i) {
        std::string filename = StringUtils::format("player_walk_images/walk_%s%d.png", baseFilename.c_str(), i);
        frame = SpriteFrame::create(filename, CCRectMake(0, 0, 70, 120));
        frameVec.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);

    CCAnimate* animate = CCAnimate::create(animation);

    Player::runAction(animate);
}

void Player::createStandFrame(const std::string& filename, const std::string& animationName) {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (!texture) {
        problemLoading(filename.c_str());
        return;
    }

    Rect rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
    SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
    if (frame) {
        frameCache->addSpriteFrame(frame, animationName);
        CCLOG("Stand frame loaded for %s", animationName.c_str());
    }
    else {
        problemLoading(("stand_" + animationName).c_str());
    }
}

void Player::setStandPose(const std::string& standPoseName) {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    SpriteFrame* frame = frameCache->getSpriteFrameByName(standPoseName);
    if (frame) {
        setSpriteFrame(frame);
        CCLOG("Set stand pose to %s", standPoseName.c_str());
    }
    else {
        CCLOG("Error: Stand pose frame for %s not found!", standPoseName.c_str());
    }
}



