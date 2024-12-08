#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "../DateManage/DateManage.h"
#include "../Constant/Constant.h"
#include <map>

// ���������
enum class CropType {
	Apple,
	Corn,
	Carrot,
};

// ����
enum class Season {
	Spring,
	Summer,
	Autumn,
	Winter,
};

// ����Ļ���
class Crop {
private:

	std::map<Season, int> seasonGrowDay;			// ÿ�����ڵ���������
protected:
	CropType cropType;		// ���������
	int growedDay;			// �Ѿ��ɳ�������
	int growthStage;		// ��ǰ�ĳɳ��׶�
	bool isInfested;		// �Ƿ����ܳ溦
	int infestedDay;		// ���ܳ溦����
	bool isDrought;			// �Ƿ����ܸɺ�
	int droughtDay;			// �ɺ�����
	bool isFertilized;		// ��ǰ�������Ƿ�ʩ��
	int cropGID;			// ��ǰͼ���Ӧͼ���GID
	cocos2d::Vec2 position;	// ��ǰ��������Ƭ��ͼ�ϵ�λ��
	int maxAliveDay;		// �����������������
public:

	// ���캯��
	Crop(const CropType& cropType,const int& cropGID, cocos2d::Vec2 position);

	// �������������,�麯��
	virtual void grow() {};

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

	// ��ȡ��ǰ��GID
	int getCurrentGID();

	// ��ȡ��ǰ���ڵĳɳ�ʱ��
	int getCurrentSeasonGrowDay(Season season);

	// ���µ�ǰͼ���GID
	virtual void updateGID() {};
};

//��������ļ̳�

// Apple�ࣺ��ʾƻ��
class Apple : public Crop {
private:

public:
	
	// ���캯��
	Apple(const cocos2d::Vec2& position);

	// ƻ������������
	void grow() override;

	// ����ͼ�����д
	void updateGID() override;
};

// Corn�ࣺ��ʾ����
class Corn : public Crop {
private:
public:
	
	// ���캯��
	Corn(const cocos2d::Vec2& position);

	// ���׵����ɺ���
	void grow() override;

	// ����ͼ����غ�
	void updateGID() override{}
};

// Carrot�ࣺ�������ܲ�
class Carrot : public Crop {
private:
public:

	// ���캯��
	Carrot(const cocos2d::Vec2& position);

	// ����ͼ�����д
	void updateGID() override {};

	// ���ܲ�������������д
	void grow() override;
};

#endif