#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>
#include "../Constant/Constant.h"

enum class RelationshipStatus {
    None,       // İ��
    Friendship, // ����
    Romance     // ����
};

class Npc : public cocos2d::Sprite {
private:
    std::string name;                   // NPC������
    std::string birthday;               // NPC������
    int friendshipLevel;                // NPC����ҵ����ܶȣ�0-100��
    std::vector<std::string> gifts;     // NPCϲ��������
    std::vector<std::string> dislikes;  // NPC���������
    std::vector<std::string> dialogues; // NPC�ĶԻ��б�
    std::string image;                  // ͼ���·��
    RelationshipStatus playerRelation;  // ����ҵĹ�ϵ��None, Friendship, Romance��

    // �Ի�����س�Ա
    cocos2d::Sprite* dialogueBox;                // �Ի��򱳾�
    cocos2d::Label* dialogueLabel;               // �Ի����е��ı���ǩ
    bool isDialogueVisible;             // ���ڱ�ǶԻ����Ƿ���ʾ

public:

    static Npc* create(const NpcInfo& npc_info);

    bool init(const NpcInfo& npc_info);

    // ��ȡNPC������
    std::string getNpcName() const;

    // ��ȡNPC������
    std::string getBirthday() const;

    // ��ȡNPC�����ܶ�
    int getFriendshipLevel() const;

    // ����NPC�����ܶ�
    void setFriendshipLevel(int level);

    // ��NPC����
    void interactWithPlayer();

    // ��NPC������
    std::string giveGift(const std::string& gift);

    // �ж�NPC�Ƿ�ϲ��ĳ������
    bool likesGift(const std::string& gift) const;

    // �ж�NPC�Ƿ�����ĳ������
    bool dislikesGift(const std::string& gift) const;

    // ����NPC�����ܶ�
    void increaseFriendship(const int amount);

    // ����NPC�����ܶ�
    void decreaseFriendship(const int amount);

    // ��ȡNPC������ϲ��������
    std::vector<std::string> getGifts() const;

    // ��ȡNPC���������������
    std::vector<std::string> getDislikes() const;

    // ����NPC��ϲ��������
    void setGifts(const std::vector<std::string>& giftList);

    // ����NPC�����������
    void setDislikes(const std::vector<std::string>& dislikeList);

    // ��ȡNPC�ĶԻ�
    std::string printDialogue() const;

    // ��ȡNPC����ҵĹ�ϵ״̬
    RelationshipStatus getPlayerRelation();

    // ��������ҵĹ�ϵ
    void setPlayerRelation(RelationshipStatus status);

    // ���NPC�ĵ�ǰ״̬
    std::string printStatus() const;
};

#endif // NPC_H