#include "Tool.h"

class FishingRod : public Tool {
public:
	// ��̬��������
	static FishingRod* create();

	// ��ʼ��
	bool init();

    // ����ʹ�ù��ߵĺ�����ִ�е���Ĳ���
    void useItem() override;
	// �ջ���͵Ķ���
	void reelInRod();
	// �Ƿ�����ʹ�ù���
	static bool isUsed;
};
