#include "Tool.h"

class FishingRod : public Tool {
public:
	// ��̬��������
	static FishingRod* create();

	// ��ʼ��
	bool init();

    // ����ʹ�ù��ߵĺ�����ִ�е���Ĳ���
    void useTool() override;
	void reelInRod();
	static bool isUsed;
};
