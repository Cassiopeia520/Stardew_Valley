#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../DateManage/Weather.h"

USING_NS_CC;

std::vector<Npc*> Farm::npcs;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	DateManage* dateManage = DateManage::getInstance();

	FarmMap* farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmMap.tmx")) {
		return false;
	}

	currentWeatherSystem = nullptr;
	backgroundMask = nullptr;

	// ����һ����ʱ����ÿ�����һ�� updateDate ����
	schedule([this, dateManage,farmMap](float deltaTime) {
		dateManage->updateDate();
		farmMap->farmMapUpdateByTime();
		this->updateWeather(dateManage->getCurrentWeather());
		}, 1.0f, "update_date_key");

	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(WINSIZE.width / 2 -farmMapSize.width / 2, WINSIZE.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// ��������NPC
	Npc* wizard = Npc::create(WIZARD_INFO);
	Npc* cleaner = Npc::create(CLEANER_INFO);
	npcs.push_back(cleaner);
	npcs.push_back(wizard);
	farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	DialogueBox::isDialogueVisible = false;

	// ���
	auto player = Player::getInstance();
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // ��ҳ�ʼλ������Ļ����
	this->addChild(player, 3);

	// �������
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		this->addChild(nameLabel, 4);
	}

	// ����
	Bag* bag = Bag::getInstance();
	if (bag) {
		this->addChild(bag, 4);
	}

	// �˳���ť
	auto closeButton = MyButton::create(ResPath::CLOSE_BUTTON_NORMAL, ResPath::CLOSE_BUTTON_HOVER);
	if (closeButton) {
		const auto closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // �������Ͻ�
		this->addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	Control* control = Control::create();
	this->addChild(control, 4);

	 // ������ʾ���ڵı�ǩ
	 if (dateManage->dateLabel) {
		 dateManage->dateLabel->setPosition(Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // ���Ͻ�λ��
		 this->addChild(dateManage->dateLabel, 5);
	 }
	return true;
}

// ũ�����������ı仯
void Farm::updateWeather(Weather weather) {
	 // �Ƴ����е���������ϵͳ
    if (currentWeatherSystem) {
        this->removeChild(currentWeatherSystem);
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
				this->removeChild(backgroundMask);
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
				this->addChild(backgroundMask, 99);									// ��ӵ��������㼶��������Ч��
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
				this->addChild(backgroundMask, 99);									// ��ӵ��������㼶��������Ч��
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
        this->addChild(currentWeatherSystem, 100);
    }
}
// �رհ�ť�Ļص�����
void Farm::closeButtonClicked(Ref* pSender) {
	Director::getInstance()->popScene();
}