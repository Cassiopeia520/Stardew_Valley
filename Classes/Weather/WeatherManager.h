#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

#include "cocos2d.h"
#include "../Date/DateManage.h"

// WeatherManager�ࣺ��������
class WeatherManager : public cocos2d::Node {
public:
    // ��̬����WeatherManager����� 
    static WeatherManager* create();

    // ÿ�ո�������
    void updateWeather(Weather weather);

    // �Ƴ���ǰ����ϵͳ
    void removeWeatherEffect();
private:
    // ���캯��
    WeatherManager();

    // ��������
    ~WeatherManager();
    
    // ��������ϵͳ
    cocos2d::ParticleSystem* currentWeatherSystem;

    // ��������
    cocos2d::LayerColor* backgroundMask;
};


#endif 
