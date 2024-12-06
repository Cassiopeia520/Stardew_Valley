#include "Npc.h"
#include <iostream>

USING_NS_CC;

// ��̬��������
Npc* Npc::create(const NpcInfo& npc_info) {
    Npc* npc = new (std::nothrow) Npc;
    if (npc && npc->init(npc_info)) {
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;
}

bool Npc::init(const NpcInfo& npc_info) {
    if (!Sprite::initWithFile(npc_info.image)) {
        return false;
    }
    name = npc_info.name;
    birthday = npc_info.birthdate;
    friendshipLevel = npc_info.friendshipLevel;
    gifts = npc_info.gifts;
    dislikes = npc_info.dislikes;
    dialogues = npc_info.dialogues;
    image = npc_info.image;

    return true;
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
void Npc::increaseFriendship(const int amount) {
    friendshipLevel += amount;
    if (friendshipLevel > 100) {
        friendshipLevel = 100;
    }
}

// ���� NPC �����ܶ�
void Npc::decreaseFriendship(const int amount) {
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