#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <vector>
#include <map>

// ���������
enum class CropType {
	Dogbane,
	Corn,
	Carrot,
};

// ����Ļ���
class Crop {
private:

protected:
	CropType cropType;		// ���������
	int growedDay;			// �Ѿ��ɳ�������
	int growthStage;		// ��ǰ�ĳɳ��׶�
	bool isInfested;		// �Ƿ����ܳ溦
	int infestedDay;		// ���ܳ溦����
	bool isDrought;			// �Ƿ����ܸɺ�
	int droughtDay;			// �ɺ�����
	bool isFertilized;		// ��ǰ�������Ƿ�ʩ��
	
	// ��ͬ���ڶ�Ӧ�������׶���������
	std::map<std::string, std::vector<int>> seasonalGrowthStageDay;
public:
	// ���캯��
	Crop(const CropType& cropType);

	// ��ʼ��
	virtual bool init();

	// �������������,�麯��
	virtual void grow() {};

	// �����������Ӱ��
	void soilInfluence(int waterLevel,int fertilizeLevel);

	// �ж���������
	bool isDead();

	// �ж��������
	bool isMature();

	// ʹ��ũҩ
	void applyPesticide();

	// ���������׶�
	void updateGrowthStage();

	// ��������
	virtual void generatePest()=0;

	// ��ȡ��ǰ���������׶�
	int getGrowthStage() const;

	// �жϳ溦
	bool judgeInfested() const;

	// ��õ�ǰ��������
	CropType getCropType() const;
};
#endif