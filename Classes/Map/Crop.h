#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "../DateManage/DateManage.h"
#include "../Constant/Constant.h"

// ���������
enum class CropType {
	Apple,
	Corn,
	Carrot,
};

// ����
enum class Season {
	Sring,
	Summer,
	Autumn,
	Winter,
};

// ����Ļ���
class Crop {
private:
	int maxGrowthDay;		// ��ĳ�������

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
	Crop(const CropType& cropType, const int& maxGrowthDay,const int& cropGID, cocos2d::Vec2 position);

	// �������������,�麯��
	virtual void grow() {};

	// ��ȡ��ǰ������Ҫ�ĳ�������
	int getMaturedDay() const;

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

	// ����ÿ��ĸ���
	void cropUpdateByDay();

	// ���µ�ǰͼ���GID
	virtual void updateGID() {};
};

//��������ļ̳�

// Apple�ࣺ��ʾƻ��
class Apple : public Crop {
private:
	std::vector<Season> season;				// �ʺ���ֲ�ļ���
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
	std::vector<Season> season;				// �ʺ���ֲ�ļ���
public:
	
	// ���캯��
	Corn(const cocos2d::Vec2& position);

	// ����ͼ����غ�
	void updateGID() override{}
};

// Carrot�ࣺ�������ܲ�
class Carrot : public Crop {
private:
	std::vector<Season> season;				// �ʺ���ֲ�ļ���
public:

	// ���캯��
	Carrot(const cocos2d::Vec2& position);

	// ����ͼ�����д
	void updateGID() override {};

	// ���ܲ�������������д
	void grow() override;
};

#endif