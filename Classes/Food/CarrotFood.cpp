#include "CarrotFood.h"
#include "../Constant/Constant.h"

// create���������ڴ��������س�ʼ����Food����
CarrotFood* CarrotFood::create() {
    CarrotFood* carrotFood = new (std::nothrow) CarrotFood();
    // ʹ�� item_info ��ʼ�� Food ��״̬
    if (carrotFood && carrotFood->init()) {
        carrotFood->autorelease();
        return carrotFood;
    }
    else {
        CC_SAFE_DELETE(carrotFood);
        return nullptr;
    }
}


// init���������ڳ�ʼ��Food������ڲ�״̬
bool CarrotFood::init() {
    return Food::init(CARROT_ITEM);
}