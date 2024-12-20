#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>

class NPC : public cocos2d::Sprite {
public:
    // 创建 NPC
    static NPC* create(const std::string& name, const std::string& spritePath);

    // 初始化 NPC
    bool init(const std::string& name, const std::string& spritePath);

    // 对话系统
    std::string getDialog() const;            // 获取当前对话
    void advanceDialog();                     // 推进到下一句对话
    void jumpToDialog(int index);             // 跳转到指定的对话内容
    void resetDialog();                       // 重置对话（回到第一句）

    // 设置 NPC 的精灵位置
    void setSpritePosition(const cocos2d::Vec2& position);

    // 获取 NPC 名称
    std::string getName() const;

private:
    // 构造和析构函数
    NPC();                                  // 构造函数（私有）
    ~NPC();                                 // 析构函数（私有）

    std::string name;                       // NPC 的名称
    cocos2d::Sprite* sprite;                // NPC 的精灵（精灵会通过 Cocos2d 进行管理）
    std::vector<std::string> dialogues;     // 对话内容集合
    int currentDialogIndex;                 // 当前对话的索引
};

#endif // NPC_H
