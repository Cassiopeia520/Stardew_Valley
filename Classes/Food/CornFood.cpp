#include "CornFood.h"
#include "../Constant/Constant.h"

// create���������ڴ��������س�ʼ����Food����
CornFood* CornFood::create() {
    CornFood* cornFood = new (std::nothrow) CornFood();
    // ʹ�� item_info ��ʼ�� Food ��״̬
    if (cornFood && cornFood->init()) {
        cornFood->autorelease();
        return cornFood;
    }
    else {
        CC_SAFE_DELETE(cornFood);
        return nullptr;
    }
}


// init���������ڳ�ʼ��Food������ڲ�״̬
bool CornFood::init() {
    return Food::init(CORN_ITEM);
}