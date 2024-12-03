#include "TileNode.h"


// �����ĳ���
void Soil::hoe() {
	isHoed = true;
	this->updateGID(64);
}

// �����Ľ�ˮ
void Soil::water() {
	if (isHoed ) {
		// �ж��������λ���Ƿ�������
		if (crop == nullptr) {
			this->updateGID(96);
		}
		// ����������״̬
		waterLevel = 10;
		isWatered = true;
	}
}

// ������ʩ��
void Soil::fertilize() {
	fertilizeLevel = 10;
	isFertilized = true;
}

// �����Ľ������ܵ�����
void Soil::interact(std::string toolName) {
	
	if (toolName=="hoe") {						// ����ǳ�ͷ����ô���г���
		hoe();
	}
	else if (toolName == "kettle") {			// �����ˮ������ô���н�ˮ
		water();
	}
	else if (toolName == "fertilizer") {		// ����Ƿ��ϣ���ô����ʩ��
		fertilize();
	}
	// ��������ɸ������ӵ��ؽ�
}