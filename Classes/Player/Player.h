#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>

class Player : public cocos2d::Sprite {
public:
	// ����ģʽ��ȡ���ʵ��
	static Player* getInstance();

	// ��ʼ�����
	bool init();

	// ��������ƶ��ķ���
	void moveByDirection(const cocos2d::Vec2& direction);

	// ��������
	void setPlayerName(const std::string& name);

	// ��ȡ����
	std::string getPlayerName() const;

private:
	// ��ҵ�ǰ�ٶ�
	cocos2d::Vec2 velocity;

	// �������
	std::string name;

	// ����ʵ��
	static Player* instance;

	// ˽�й��캯������ֹ���ʵ������ȷ��Ψһ��
	Player();
	~Player();

	// ��ֹ�����͸�ֵ
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
};

#endif