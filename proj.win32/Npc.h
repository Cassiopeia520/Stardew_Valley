#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <map>

enum class RelationshipStatus {
    None,       // İ��
    Friendship, // ����
    Romance     // ����
};

class Npc {
private:
    std::string name;                   // NPC������
    std::string birthday;               // NPC������
    int friendshipLevel;                // NPC����ҵ����ܶȣ�0-100��
    std::vector<std::string> gifts;     // NPCϲ��������
    std::vector<std::string> dislikes;  // NPC���������
    std::vector<std::string> dialogues; // NPC�ĶԻ��б�
    RelationshipStatus playerRelation;  // ����ҵĹ�ϵ��None, Friendship, Romance��
    std::map<std::string, RelationshipStatus> npcRelations; // NPC֮��Ĺ�ϵ

public:
    // ���캯��
    Npc(std::string name, std::string birthday,
        std::vector<std::string> gifts,
        std::vector<std::string> dislikes,
        std::vector<std::string> dialogues);

    // ��ȡNPC������
    std::string getName() const;

    // ��ȡNPC������
    std::string getBirthday() const;

    // ��ȡNPC�����ܶ�
    int getFriendshipLevel() const;

    // ����NPC�����ܶ�
    void setFriendshipLevel(int level);

    // ��NPC����
    void interactWithPlayer();

    // ��NPC������
    void giveGift(const std::string& gift);

    // �ж�NPC�Ƿ�ϲ��ĳ������
    bool likesGift(const std::string& gift) const;

    // �ж�NPC�Ƿ�����ĳ������
    bool dislikesGift(const std::string& gift) const;

    // ����NPC�����ܶ�
    void increaseFriendship(int amount);

    // ����NPC�����ܶ�
    void decreaseFriendship(int amount);

    // ��ȡNPC������ϲ��������
    std::vector<std::string> getGifts() const;

    // ��ȡNPC���������������
    std::vector<std::string> getDislikes() const;

    // ����NPC��ϲ��������
    void setGifts(const std::vector<std::string>& giftList);

    // ����NPC�����������
    void setDislikes(const std::vector<std::string>& dislikeList);

    // ��ȡNPC�ĶԻ�
    void printDialogue() const;

    // ��ȡNPC����ҵĹ�ϵ״̬
    RelationshipStatus getPlayerRelation() const;

    // ��������ҵĹ�ϵ
    void setPlayerRelation(RelationshipStatus status);

    // ����NPC֮��Ĺ�ϵ
    void setNpcRelation(const std::string& npcName, RelationshipStatus status);

    // ��ȡNPC����һNPC�Ĺ�ϵ
    RelationshipStatus getNpcRelation(const std::string& npcName) const;

    // ���NPC�ĵ�ǰ״̬
    void printStatus() const;

    // ѯ��NPC֮��Ĺ�ϵ
    void askAboutNocRelation(const std::string& otherNpcName) const;
};

#endif // NPC_H
