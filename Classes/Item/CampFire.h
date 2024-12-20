/****************************************************************
 * File Function: �����࣬�̳�Item�࣬�������ʳ��
 * Author:        Τ���
 ****************************************************************/
#ifndef __CampFire_H__
#define __CampFire_H__

#include "Item.h"

// �����࣬�̳���Item��
class CampFire : public Item {
public:
    // ��ʼ������������������ơ�ͼƬ��
    bool init(const ItemInfo& item_info) override;

    // ����ģʽ��ȡʵ��
    static CampFire* getInstance();

    // ��������
    CampFire* create(const ItemInfo& item_info);

    // ʹ�����𣺽�ʳ�￾�죨�����������
    void useItem() override;

    // get set status
    bool getStatus() const { return status; }
    bool setStatus(bool value) { return status = value; }

private:
    // ����ʵ��
    static CampFire* instance;

    // ����״̬
    static bool status;
};

#endif // __CampFire_H__
