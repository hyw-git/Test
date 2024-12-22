#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
#include <string>
#include <vector>

class NPC : public cocos2d::Node {
public:
    // 创建 NPC 对象
    static NPC* create(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues);

    // 初始化 NPC 对象
    bool init(const std::string& name, const std::string& spritePath, const std::vector<std::string>& dialogues);

    // 对话相关功能
    std::string getCurrentDialogue() const;    // 获取当前对话
    void advanceDialogue();                    // 推进到下一句对话
    void resetDialogue();                      // 重置对话（回到第一句）

    // 设置精灵的位置
    void setSpritePosition(const cocos2d::Vec2& position);

    // 获取 NPC 名称
    std::string getName() const;

private:
    NPC();                                    // 构造函数
    virtual ~NPC();                           // 析构函数

    void createTouchListener();               // 创建触摸事件监听器
    void updateDialogueUI();                  // 更新对话 UI 显示

    std::string m_name;                       // NPC 名称
    cocos2d::Sprite* m_sprite;                // NPC 精灵
    cocos2d::Label* m_dialogueLabel;          // 显示对话的标签
    std::vector<std::string> m_dialogues;     // 对话内容集合
    int m_currentDialogueIndex;               // 当前对话的索引
};

#endif // __NPC_H__
