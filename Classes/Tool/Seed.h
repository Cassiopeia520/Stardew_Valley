#ifndef __SEED_H__
#define __SEED_H__

#include "Tool.h"
#include "cocos2d.h"
#include <string>

enum class SeedType {
	DogbaneSeed,
	CornSeed,
	CarrotSeed
};

// Seed�ࣺ�̳��Թ����࣬��ʾ��Ʒ�е�ƻ������
class Seed : public Tool {
private:
	std::string seedName;
public:
	// ��ʼ������
	bool init(const SeedType& seedType);

	// ʹ�ù���
	void useItem() override;
};

// DogbaneSeed�ࣺ�̳���Seed�࣬��ʾ���������
class DogbaneSeed :public Seed {
public:
	// ��̬��������
	static DogbaneSeed* create();
};

// CornSeed�ࣺ�̳���Seed�࣬��ʾ��������
class CornSeed : public Seed {
public:
	// ��̬��������
	static CornSeed* create();
};

// CarrotSeed�ࣺ�̳���Seed�࣬��ʾ���ܲ�����
class CarrotSeed :public Seed {
public:
	// ��̬��������
	static CarrotSeed* create();
};

#endif
