#include "Player.h"

USING_NS_CC;

// ��ʼ����̬��Ա����
Player* Player::instance = nullptr;

Player::Player() : velocity(Vec2::ZERO), name("") {}

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
	if (!Sprite::initWithFile("playerImage/downStill.png")) {
		return false;
	}

	// ��ʼ�ٶ�Ϊ��
	velocity = Vec2::ZERO;

	schedule([this](float dt) {
			auto position = getPosition();
			setPosition(position + velocity * dt);

			// ��ȡ����ߴ�
			auto visibleSize = Director::getInstance()->getVisibleSize();
			const Vec2 origin = Director::getInstance()->getVisibleOrigin();
			// �߽��⣬��ֹ����Ƴ���Ļ
			position = getPosition();
			const Vec2 playerSize(Player::getInstance()->getContentSize());
			position.x = std::max(origin.x + playerSize.x / 2, std::min(position.x, origin.x + visibleSize.width - playerSize.x / 2));
			position.y = std::max(origin.y + playerSize.y / 2, std::min(position.y, origin.y + visibleSize.height - playerSize.y / 2));
			setPosition(position);
		}, "player_movement");

	return true;
}

void Player::moveByDirection(const Vec2& direction) {
	velocity = direction * 200.0f;
}

void Player::stopMoving() {
	velocity = Vec2::ZERO; // ֹͣ�ƶ�
}

void Player::setPlayerName(const std::string& name) {
	this->name = name;
}

std::string Player::getPlayerName() const {
	return name;
}