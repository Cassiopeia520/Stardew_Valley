#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"

// ���������
enum class CropType {
	APPLE,
	CORN,
	CARROT,
};

// ����
enum class Season {
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
};

// ����Ļ���
class Crop {
private:

protected:
	// ���������
	CropType cropType;
	// ��ĳ�������
	int maxGrowthDay;
	// ��ǰ�ĳɳ��׶�
	int growthStage;
	// �ջ����ֲ����
	Season season;
	// �Ƿ����ܳ溦
	bool isInfested;
	// ���ܳ溦����
	int infestedDay;
	// �Ƿ�ɺ�
	bool isDrought;
	// ��ǰ����ֵ
	int fertilizedLevel;
	// ��ǰͼ���Ӧͼ���GID
	int cropGID;
	// ��ǰ��������Ƭ��ͼ�ϵ�λ��
	cocos2d::Vec2 position;
public:
	// ���캯��
	Crop(const CropType& cropType,const int& maxGrowthDay,const Season& season,
		const int& cropGID,cocos2d::Vec2 position):
		cropType(cropType),maxGrowthDay(maxGrowthDay),growthStage(0),
		season(season),isInfested(false),isDrought(false),
		fertilizedLevel(0),cropGID(cropGID),position(position) ,
		infestedDay(0)
	{}

	// �������������,�麯��
	virtual void grow();

	// �ж��Ƿ����
	bool isMature() const;

	// ��ˮ
	void irrigate();

	// ʩ��
	void fertilize();

	// ʹ��ũҩ
	void applyPesticide();

	// ����ķ���
	void harvest();
};

//��������ļ̳�

// ƻ������
class Apple : public Crop {
private:
	Season season;
public:
	// ��ȡ��ǰ��GID
	int getCurrentGID();
};

// ��������
class Corn : public Crop {
private:
	Season season;
public:
	// ��ȡ��ǰ��GID
	int getCurrentGID();
};

// ���ܲ�����
class Carrot : public Crop {
private:
	// ��ǰ��GID
	int currentGID;
public:
	// ��ȡ��ǰ��GID
	int getCurrentGID();
};

#endif