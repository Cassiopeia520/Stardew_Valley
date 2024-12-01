#include "Npc.h"
#include <iostream>
#include <map>

// ���캯������ʼ�� NPC �����֡����ա����ܶȡ�ϲ����������������Ի�
Npc::Npc(const std::string& name, const std::string& birthday,
    const std::vector<std::string>& favorateGifts,
    const std::vector<std::string>& dislikedGifts,
    const std::vector<std::string>& dialogues,
    const std::string& imagePath)
    : name(name), birthday(birthday), friendshipLevel(0), gifts(favorateGifts), dislikes( dislikedGifts), dialogues(dialogues), image(imagePath), playerRelation(RelationshipStatus::None) {
}

Npc::Npc(const Npc& other)
    : name(other.name),
    birthday(other.birthday),
    friendshipLevel(other.friendshipLevel),
    playerRelation(other.playerRelation),
    gifts(other.gifts), 
    dislikes(other.dislikes),
    dialogues(other.dialogues) {
    // ��������
    sprite = Sprite::create(other.image);
}

Npc::Npc(){}

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
}

// �� NPC ����
void Npc::interactWithPlayer() {
    increaseFriendship(5);
    printDialogue();  // �������ӡ��ǰ�ĶԻ�
}

// �� NPC ������
std::string Npc::giveGift(const std::string& gift) {
    std::string str = "you sent " + name + " " + gift + ".\n";

    if (likesGift(gift)) {
        str += name + " likes it very much.";
        increaseFriendship(10);
    }
    else if (dislikesGift(gift)) {
        str += name + " doesn't like it.";
        decreaseFriendship(10);
    }
    else {
        str += name + " said nothing about it.";
    }
    return str;
}

// �ж� NPC �Ƿ�ϲ��ĳ������
bool Npc::likesGift(const std::string& gift) const {
    for (std::string item : gifts) {
        if (item == gift)
            return true;
    }
    return false;
}

// �ж� NPC �Ƿ�����ĳ������
bool Npc::dislikesGift(const std::string& gift) const {
    for (std::string item : dislikes) {
        if (item == gift)
            return true;
    }
    return false;
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
RelationshipStatus Npc::getPlayerRelation() {
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
    return playerRelation;
}

// ����NPC����ҵĹ�ϵ״̬
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// ��� NPC �ĵ�ǰ״̬
std::string Npc::printStatus() const {
    std::string res = "friendshipLevel with " + name + ":  " + std::to_string(friendshipLevel);
    if (friendshipLevel >= 80)
        res += "\nRomance";
    else if (friendshipLevel >= 50)
        res += "\nFriend";
    else
        res += "\nNone";
    return res;
}