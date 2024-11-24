#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>
#include <map>

// �����
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

	//ֹͣ�ƶ�
	void stopMoving();

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

	//����
	std::map<std::string, cocos2d::Animate*> animations;
	std::string currentAnimationName;
	cocos2d::Vec2 lastDirection;

	void loadAnimations();
	void createWalkFrames(const std::string& baseFilename, const std::string& animationName, int frameCount);
	void createStandFrame(const std::string& filename, const std::string& animationName);
	void playAnimation(const std::string& animationName);
	void setStandPose(const std::string& standPoseName);
};

#endif