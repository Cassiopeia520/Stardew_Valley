#include "Tool.h"

// ������
class Scythe : public Tool {
public:
	// ��̬��������
	static Scythe* create();

	// ��ʼ��
	bool init();

	// ʹ�ù���
	void useItem() override;
};