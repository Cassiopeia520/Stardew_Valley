#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "cocos2d.h"
#include "../DateManage/DateManage.h"

// ǰ������ FarmScene ��
class Farm;

class WeatherManager : public cocos2d::Node {
public:
    static WeatherManager* create(Farm* farmScene);
    bool init(Farm* farmScene);

    // ���õ�ǰ����
    void updateWeather(Weather weather);

private:
    Farm* farmScene; // FarmScene ����
    cocos2d::ParticleSystemQuad* currentWeatherSystem; // ��ǰ����������ϵͳ
    cocos2d::LayerColor* backgroundMask; // ��������
};

#endif 
