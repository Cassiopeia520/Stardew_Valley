#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"
#include "Crop.h"
#include "Animal.h"

class Entity {
protected:
    // ʵ������ (e.g., "crop", "animal")
    std::string type;  
    // ʵ������λ��
    Vec2 position;     
public:
    // ���캯��
    Entity(const std::string& entityType, const Vec2& pos)
        : type(entityType), position(pos) {}

    // ��ȡʵ������
    virtual std::string getType() const {
        return type;
    }

    // ��ȡλ��
    virtual Vec2 getPosition() const {
        return position;
    }

    // ����λ��
    virtual void setPosition(const Vec2& newPosition) {
        position = newPosition;
    }

    // ÿ�ո����߼� (�麯��������ʵ�־����߼�)
    //virtual void updateDaily() = 0;

    // ����������
    virtual ~Entity() {}
};

#endif