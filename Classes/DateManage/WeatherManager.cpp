#include "WeatherManager.h"
#include "../Constant/Constant.h"

USING_NS_CC;


WeatherManager::WeatherManager()
    : currentWeatherSystem(nullptr), backgroundMask(nullptr) {
}

WeatherManager::~WeatherManager() {
    removeWeatherEffect();
}

WeatherManager* WeatherManager::create() {
    WeatherManager* weatherManger = new WeatherManager();
    if (weatherManger && weatherManger->init()) {
        weatherManger->autorelease();
        return weatherManger;
    }
    CC_SAFE_DELETE(weatherManger);
    return nullptr;
}

// ÿ�ո�������
void WeatherManager::updateWeather(Weather weather) {
    removeWeatherEffect();  // �Ƴ����е�����Ч��

    // �Ƴ����е���������ϵͳ
    if (currentWeatherSystem) {
        removeChild(currentWeatherSystem);
        currentWeatherSystem = nullptr;
    }

    // ��������ѡ��ͬ������ϵͳ
    switch (weather) {
    case Weather::Sunny:
        // ���죺����ʹ�ù��Ч����򵥵����챳��
        currentWeatherSystem = ParticleSun::create();
        currentWeatherSystem->setPosition(WINSIZE.width - SUN_OFFSET, WINSIZE.height - SUN_OFFSET); // ���Ͻ�
        currentWeatherSystem->setStartColor(Color4F(1.0f, 0.9f, 0.5f, 1.0f));	// ̫������ɫ
        currentWeatherSystem->setEndColor(Color4F(1.0f, 0.8f, 0.3f, 0.8f));		// ̫���������ɫ
        currentWeatherSystem->setSpeed(0);										// �޷�
        currentWeatherSystem->setLife(0);										// ����Ҫ�������ڣ�ֻ��װ��Ч��

        // ɾ����������
        if (backgroundMask) {
            removeChild(backgroundMask);
            backgroundMask = nullptr;
        }
        break;

    case Weather::LightRain:
        // С�꣺����С�������ϵͳ
        currentWeatherSystem = ParticleRain::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// ��Ļ����
        currentWeatherSystem->setStartColor(Color4F(0.4f, 0.4f, 1.0f, 1.0f));	// ǳ��ɫ���
        currentWeatherSystem->setEndColor(Color4F(0.2f, 0.2f, 0.8f, 0.8f));		// ��ν���
        currentWeatherSystem->setSpeed(500);									// ����ٶ�
        currentWeatherSystem->setSpeedVar(50);									// ����һЩ�ٶȵ������
        currentWeatherSystem->setStartSize(10.0f);								// ������εĴ�С
        currentWeatherSystem->setEndSize(5.0f);									// ��С

        // ��ӱ�������
        if (!backgroundMask) {
            backgroundMask = LayerColor::create(Color4B(0, 0, 0, 32));			// ��͸����ɫ
            addChild(backgroundMask, 99);									// ��ӵ��������㼶��������Ч��
        }
        break;

    case Weather::HeavyRain:
        // ���꣺���ø�����ٶȺ͸�������

        currentWeatherSystem = ParticleRain::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// ��Ļ����
        currentWeatherSystem->setStartColor(Color4F(0.4f, 0.4f, 1.0f, 1.0f));	// ��ɫ���
        currentWeatherSystem->setEndColor(Color4F(0.2f, 0.2f, 0.8f, 0.8f));		// ����
        currentWeatherSystem->setTotalParticles(600);							// �������ӵ���������������
        currentWeatherSystem->setSpeed(800);									// �����ٶ�
        currentWeatherSystem->setSpeedVar(100);									// �����ٶȵ������
        currentWeatherSystem->setStartSize(15.0f);								// ��������
        currentWeatherSystem->setEndSize(10.0f);								// ��С
        // ��ӱ�������
        if (!backgroundMask) {
            backgroundMask = LayerColor::create(Color4B(0, 0, 0, 64));			// ����İ�͸����ɫ
            addChild(backgroundMask, 99);									// ��ӵ��������㼶��������Ч��
        }
        break;

    case Weather::Snowy:
        // ѩ�죺ѩ��������ϵͳ
        currentWeatherSystem = ParticleSnow::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// ��Ļ����
        currentWeatherSystem->setStartColor(Color4F(1.0f, 1.0f, 1.0f, 1.0f));	// ��ɫѩ��
        currentWeatherSystem->setEndColor(Color4F(0.8f, 0.8f, 0.8f, 0.8f));		// ����Ϊ͸��
        currentWeatherSystem->setSpeed(100);									// �����ѩ���ٶ�
        currentWeatherSystem->setSpeedVar(20);									// ��΢�е������
        currentWeatherSystem->setStartSize(10.0f);								// �еȴ�Сѩ��
        currentWeatherSystem->setEndSize(5.0f);									// ��С
        break;
    }

    // �������ϵͳ������
    if (currentWeatherSystem) {
        addChild(currentWeatherSystem, 100);
    }
}

// �Ƴ���ǰ����Ч��
void WeatherManager::removeWeatherEffect() {
    if (currentWeatherSystem) {
        removeChild(currentWeatherSystem);
        currentWeatherSystem = nullptr;
    }

    if (backgroundMask) {
        removeChild(backgroundMask);
        backgroundMask = nullptr;
    }
}