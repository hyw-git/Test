#ifndef _CHART_LAYER_H_
#define _CHART_LAYER_H_

#include "cocos2d.h"
#include "NPC.h"

class ChartLayer : public cocos2d::Layer
{
public:
    ChartLayer();                    // 构造函数
    ~ChartLayer();                   // 析构函数

    static ChartLayer* create(NPC* npc);  // 创建ChartLayer
    virtual bool init(NPC* npc);         // 初始化方法

    // 更新对话内容
    void updateDialog();

    // 关闭聊天界面
    void closeChat();

private:
    // 按钮回调函数
    void onNextButtonClicked(cocos2d::Ref* sender);  // 推进对话按钮
    void onQuitButtonClicked(cocos2d::Ref* sender);  // 退出按钮

    NPC* currentNPC; // 当前对话的 NPC
};

#endif // _CHART_LAYER_H_
