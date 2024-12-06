#include "DialogueBox.h"

USING_NS_CC;

bool DialogueBox::isDialogueVisible = false;

DialogueBox* DialogueBox::create(Npc* npc) {
    DialogueBox* ret = new DialogueBox();
    if (ret && ret->init(npc)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DialogueBox::init(Npc* npc) {
    if (!Node::init()) {
        return false;
    }

    this->npc = npc;
    // �����Ի��򱳾�
    dialogueBackground = Sprite::create(DIALOGUE_BACKGROUND);
    if (!dialogueBackground) {
        return false;
    }
    dialogueBackground->setContentSize(Size(TALKING_BOX_WIDTH, TALKING_BOX_HEIGHT)); // ���öԻ����С
    dialogueBackground->setPosition(Vec2(TALKING_BOX_X, TALKING_BOX_Y));  // ���öԻ���λ��

    // ��������ʾNPC�ĶԻ�����
    dialogueLabel = Label::createWithTTF(npc->printDialogue(), ResPath::FONT_TTF, 44);
    // �������ֿ�
    dialogueLabel->setDimensions(LABEL_WIDTH, LABEL_HEIGHT);
    dialogueLabel->setPosition(Vec2(dialogueBackground->getPositionX() - 240, dialogueBackground->getPositionY()));
    dialogueLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    dialogueLabel->setTextColor(Color4B::WHITE);

    // NPC����
    std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png";
    npcTalkImage = Sprite::create(npcImageName);
    npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));

    // NPC����
    nameLabel = Label::createWithTTF(npc->getNpcName(), ResPath::FONT_TTF, 40);
    nameLabel->setPosition(Vec2(dialogueBackground->getPositionX() + 360, dialogueBackground->getPositionY() - 140));
    nameLabel->setTextColor(Color4B::WHITE);

    return true;
}

void DialogueBox::showInitialDialogue() {
    // ��ǶԻ�������ʾ
    isDialogueVisible = true;

    this->addChild(dialogueBackground);
    this->addChild(dialogueLabel);
    this->addChild(npcTalkImage);
    this->addChild(nameLabel);

    // ��������¼�������
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [listener, this](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDialogueVisible) {
            // ��ʾѡ�ť
            showDialogueOptions(listener);
        }
        };
    // �������¼����������¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void DialogueBox::showDialogueOptions(EventListenerMouse* lastListener) {
    dialogueLabel->setVisible(false);
    _eventDispatcher->removeEventListener(lastListener);
    auto listener = EventListenerMouse::create();
    // ����ѡ�ť
    // ѡ���ı�����
    for (size_t i = 0; i < options.size(); ++i) {
        auto optionButton = ui::Button::create();
        optionButton->setTitleText(options[i]);
        optionButton->setTitleFontSize(30);
        optionButton->setTitleColor(Color3B::WHITE);
        optionButton->setPosition(Vec2(300, 300 - (i * 60)));
        optionButtons.push_back(optionButton); // ��ӵ���ť����
        optionButton->addClickEventListener([this, i](Ref* sender) {
            updateDialogueAfterOptionSelected(i);
            });
        this->addChild(optionButton);
    }
}


void DialogueBox::updateDialogueAfterOptionSelected(int optionIndex) {
    // ��������ѡ�ť
    for (auto button : optionButtons) {
        button->setVisible(false);
    }

    // ���¶Ի�������
    std::string newDialogue;
    switch (optionIndex) {
        case 0:
            newDialogue = npc->printStatus();
            break;
        case 1:
            newDialogue = "Not yet";
            break;
        case 2:
            newDialogue = "Upcoming festival: " + getNextFestival();
            break;
        case 3:
            newDialogue = npc->giveGift("Milk");
            npc->interactWithPlayer();
            break;
        default:
            break;
    }

    // ���¶Ի����е�����
    dialogueLabel->setString(newDialogue);
    dialogueLabel->setVisible(true);
    // ���´�������¼�������
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [=](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
            closeDialogue(listener);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void DialogueBox::closeDialogue(EventListenerMouse* lastListener) {
    _eventDispatcher->removeEventListener(lastListener);
    isDialogueVisible = false;
    this->removeFromParent();  // �Ƴ��Ի���
}

void DialogueBox::initMouseListener() {
    // ��������¼�������
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            // ����Ի������������رնԻ���
            if (!this->getBoundingBox().containsPoint(mouseEvent->getLocation())) {
                closeDialogue(mouseListener);
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

// ��ȡ����
std::string DialogueBox::getNextFestival() {

    // ��ȡ���ڵ���
    DateManage* dateManager = DateManage::getInstance();

    std::string res = "Today is " + dateManager->getCurrentDate() + "!\n";
    if (dateManager->isFestivalDay()) {
        int dayInSeason = dateManager->getCurrentDayInSeason();
        if (dateManager->getCurrentSeason() == "Spring" && dayInSeason == 7)
            res += SPRING_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Summer" && dayInSeason == 15)
            res += SUMMER_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Fall" && dayInSeason == 5)
            res += FALL_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Winter" && dayInSeason == 25)
            res += WINTER_CONVERSATION;
    }

    FarmMap* farmMap = FarmMap::getInstance();
    DateManage* dateManage = DateManage::getInstance();
    for (Festival* festival : dateManage->festivals) {
        std::string season, day, curSeason;
        std::istringstream stream(festival->getEventDate());
        stream >> season; // ��ȡ����
        stream >> day;    // ��ȡ����
        int date = std::stoi(day);

        std::istringstream streamCur(dateManager->getCurrentDate());
        streamCur >> curSeason >> day;
        if (season == dateManager->getCurrentSeason() && date > std::stoi(day))
            return festival->getEventName() + "is coming soon!";
        else if (season > dateManager->getCurrentSeason())
            return festival->getEventName() + "is coming soon!";
    }
    return "waiting for next year..";
}