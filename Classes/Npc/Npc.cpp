#include "Npc.h"
#include <iostream>
#include <map>

// ���캯������ʼ�� NPC �����֡����ա����ܶȡ�ϲ����������������Ի�
Npc::Npc(const std::string& name, const std::string& birthdate,
    const std::vector<std::string>& favoriteGifts,
    const std::vector<std::string>& dislikedGifts,
    const std::vector<std::string>& dialogues,
    const std::string& imagePath)
    : name(name), friendshipLevel(0), playerRelation(RelationshipStatus::None), dialogues(dialogues) {

    // ����NPC�ľ���ͼ��
    sprite = Sprite::create(imagePath);  // ���� std::string ���͵�ͼ��·��
}

Npc::Npc()
{
}

// ��ȡ NPC ������
std::string Npc::getNpcName() const {
    return name;
}

// ��ȡ NPC ������
std::string Npc::getBirthday() const {
    return birthday;
}

// ��ȡ NPC �����ܶ�
int Npc::getFriendshipLevel() const {
    return friendshipLevel;
}

// ���� NPC �����ܶ�
void Npc::setFriendshipLevel(int level) {
    if (level < 0) {
        friendshipLevel = 0;
    }
    else if (level > 100) {
        friendshipLevel = 100;
    }
    else {
        friendshipLevel = level;
    }

    // �������ܶȵ�������ҵĹ�ϵ
    if (friendshipLevel >= 80) {
        playerRelation = RelationshipStatus::Romance;
    }
    else if (friendshipLevel >= 50) {
        playerRelation = RelationshipStatus::Friendship;
    }
    else {
        playerRelation = RelationshipStatus::None;
    }
}

// �� NPC ����
void Npc::interactWithPlayer() {
    increaseFriendship(5);
    printDialogue();  // �������ӡ��ǰ�ĶԻ�
}

// �� NPC ������
void Npc::giveGift(const std::string& gift) {
    std::cout << "���͸� " << name << " " << gift << "��" << std::endl;

    if (likesGift(gift)) {
        std::cout << name << " ��ϲ��������" << std::endl;
        increaseFriendship(10);
    }
    else if (dislikesGift(gift)) {
        std::cout << name << " ����ϲ��������" << std::endl;
        decreaseFriendship(5);
    }
    else {
        std::cout << name << " ���������û���ر�ĸо���" << std::endl;
    }
}

// �ж� NPC �Ƿ�ϲ��ĳ������
bool Npc::likesGift(const std::string& gift) const {
    return std::find(gifts.begin(), gifts.end(), gift) != gifts.end();
}

// �ж� NPC �Ƿ�����ĳ������
bool Npc::dislikesGift(const std::string& gift) const {
    return std::find(dislikes.begin(), dislikes.end(), gift) != dislikes.end();
}

// ���� NPC �����ܶ�
void Npc::increaseFriendship(int amount) {
    friendshipLevel += amount;
    if (friendshipLevel > 100) {
        friendshipLevel = 100;
    }
}

// ���� NPC �����ܶ�
void Npc::decreaseFriendship(int amount) {
    friendshipLevel -= amount;
    if (friendshipLevel < 0) {
        friendshipLevel = 0;
    }
}

// ��ȡ NPC ������ϲ��������
std::vector<std::string> Npc::getGifts() const {
    return gifts;
}

// ��ȡ NPC ���������������
std::vector<std::string> Npc::getDislikes() const {
    return dislikes;
}

// ���� NPC ��ϲ��������
void Npc::setGifts(const std::vector<std::string>& giftList) {
    gifts = giftList;
}

// ���� NPC �����������
void Npc::setDislikes(const std::vector<std::string>& dislikeList) {
    dislikes = dislikeList;
}

// ��ȡ NPC �ĶԻ�
std::string Npc::printDialogue() const {
    if (friendshipLevel >= 80) {
        return dialogues[2];
    }
    else if (friendshipLevel >= 50) {
        return dialogues[1];
    }
    else {
        return dialogues[0];
    }

    return "";
}

// ��ȡNPC����ҵĹ�ϵ״̬
RelationshipStatus Npc::getPlayerRelation() const {
    return playerRelation;
}

// ����NPC����ҵĹ�ϵ״̬
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// ��� NPC �ĵ�ǰ״̬
void Npc::printStatus() const {
    std::cout << "NPC: " << name << std::endl;
    std::cout << "����: " << birthday << std::endl;
    std::cout << "���ܶ�: " << friendshipLevel << std::endl;
    std::cout << "����ҵĹ�ϵ: " << (playerRelation == RelationshipStatus::Romance ? "����" :
        playerRelation == RelationshipStatus::Friendship ? "����" : "İ��") << std::endl;
    std::cout << std::endl;
}