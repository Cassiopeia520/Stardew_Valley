#ifndef __MOVEMENTBEHAVIOR_H__
#define __MOVEMENTBEHAVIOR_H__

#include "cocos2d.h"

/*
 * Class Name:     MovementBehavior
 * Class Function: �ƶ�������
 */
class MovementBehavior {
public:
	// ����������
	virtual ~MovementBehavior() {};

	// ���������仯
	virtual void weatherChanged(float& radius, float& interval)=0;
};

#endif // !__MOVEMENTBEHAVIOR_H__

