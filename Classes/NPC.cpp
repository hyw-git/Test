#include "NPC.h"

bool NPC::init(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues) {
    // 创建NPC精灵
    auto npcSprite = cocos2d::Sprite::create("npc_image.png");
    if (!npcSprite) {
        return false; // 加载精灵失败
    }
    npcSprite->setPosition(cocos2d::Vec2(400, 300)); // 设置NPC的位置
    this->addChild(npcSprite);  // 将精灵添加到节点

    // 创建显示对话的Label
    auto dialogueLabel = cocos2d::Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    if (!dialogueLabel) {
        return false; // 创建对话框标签失败
    }
    dialogueLabel->setPosition(cocos2d::Vec2(400, 150)); // 设置对话框的位置
    this->addChild(dialogueLabel);  // 将对话Label添加到节点

    return true;
}

std::string NPC::getCurrentDialogue() const {
    if (currentDialogueIndex < dialogues.size()) {
        return dialogues[currentDialogueIndex];
    }
    return "没有更多对话了。";
}

void NPC::advanceDialogue() {
    if (currentDialogueIndex < dialogues.size() - 1) {
        ++currentDialogueIndex;
        dialogueLabel->setString(getCurrentDialogue());  // 更新对话框内容
    }
    else {
        dialogueLabel->setString("对话结束。");
    }
}

void NPC::jumpToDialogue(int index) {
    if (index >= 0 && index < dialogues.size()) {
        currentDialogueIndex = index;
        dialogueLabel->setString(getCurrentDialogue());  // 更新对话内容
    }
    else {
        CCLOG("无效的对话索引。");
    }
}

std::string NPC::getName() const {
    return m_name;
}

void NPC::resetDialogue() {
    currentDialogueIndex = 0;
    dialogueLabel->setString(getCurrentDialogue());
}

void NPC::onPlayerInteraction() {
    advanceDialogue();  // 玩家点击时推进对话
}

NPC* NPC::create(const std::string& npcName, const std::vector<std::string>& npcDialogues) {
    NPC* npc = new NPC(npcName, npcDialogues);  // 创建 NPC 对象
    if (npc && npc->init()) {
        return npc;  // 返回创建成功的 NPC 对象
    }
    else {
        delete npc;  // 如果初始化失败，手动删除对象
        return nullptr;  // 创建失败
    }
}