#ifndef NPC_H
#define NPC_H

#include "cocos2d.h" // 包含 Cocos2d 的头文件
#include <string>
#include <vector>

USING_NS_CC; 

class NPC : public Node {
public:
    NPC();
    virtual ~NPC();

    // 创建 NPC 对象的静态方法
    static NPC* create(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues);

    // 初始化 NPC
    virtual bool init(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues);

    // 获取当前对话内容
    std::string getCurrentDialogue() const;

    // 对话相关方法
    void advanceDialogue(); // 推进对话
    void resetDialogue();   // 重置对话
    void jumpToDialogue(int index); // 跳转到指定对话

private:
    std::string m_name; // NPC 名称
    Sprite* m_sprite;   // NPC 的精灵对象
    std::vector<std::string> m_dialogues; // 对话内容列表
    size_t m_currentDialogueIndex; // 当前对话的索引
};

#endif // NPC_H
