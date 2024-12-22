#include "NPC.h"

NPC::NPC() : m_sprite(nullptr), m_currentDialogueIndex(0) {}

NPC::~NPC() {}

NPC* NPC::create(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues) {
    NPC* npc = new (std::nothrow) NPC();
    if (npc && npc->init(name, spritePath, dialogues)) {
        npc->autorelease();
        return npc;
    }
    delete npc;
    return nullptr;
}

bool NPC::init(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues) {
    if (!Node::init()) {
        return false;
    }

    m_name = name;
    m_dialogues = dialogues;
    m_currentDialogueIndex = 0;

    // 创建 NPC 的精灵
    m_sprite = Sprite::create(spritePath);
    if (!m_sprite) {
        CCLOG("Error: Unable to load sprite for NPC!");
        return false;
    }

    // 添加 NPC 的精灵到当前节点
    this->addChild(m_sprite);

    return true;
}

std::string NPC::getCurrentDialogue() const {
    if (m_currentDialogueIndex < m_dialogues.size()) {
        return m_dialogues[m_currentDialogueIndex];
    }
    return "No more dialogue.";
}

void NPC::advanceDialogue() {
    if (m_currentDialogueIndex < m_dialogues.size() - 1) {
        ++m_currentDialogueIndex;
    }
}

void NPC::resetDialogue() {
    m_currentDialogueIndex = 0;
}

void NPC::jumpToDialogue(int index) {
    if (index >= 0 && index < m_dialogues.size()) {
        m_currentDialogueIndex = index;
    }
}
