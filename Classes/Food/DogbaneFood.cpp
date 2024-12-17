#include "DogbaneFood.h"
#include "../Constant/Constant.h"

// create���������ڴ��������س�ʼ����Food����
DogbaneFood* DogbaneFood::create() {
    DogbaneFood* dogbaneFood = new (std::nothrow) DogbaneFood();
    // ʹ�� item_info ��ʼ�� Food ��״̬
    if (dogbaneFood && dogbaneFood->init()) {
        dogbaneFood->autorelease();
        return dogbaneFood;
    }
    else {
        CC_SAFE_DELETE(dogbaneFood);
        return nullptr;
    }
}


// init���������ڳ�ʼ��Food������ڲ�״̬
bool DogbaneFood::init() {
    return Food::init(DOGBANE_ITEM);
}