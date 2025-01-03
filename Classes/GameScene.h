#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "CommunitySystem.h"
USING_NS_CC;

class GameScene : public cocos2d::Scene {
public:
    GameScene();
    static GameScene* createScene(); // 创建场景
    virtual bool init();             // 初始化场景
    void update(float dt);           // 每帧更新

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(GameScene);

private:
    CommunitySystem communitySystem;  // 社区系统管理器
    std::string currentDate;          // 当前日期

    // 私有方法
    void initializeCommunity();      // 初始化社区居民和节日
    void updateGameDay();            // 更新游戏时间和事件
    void updateTaskProgress();       // 更新任务进度
    std::string getDayFromTime();    // 根据时间获取当前游戏中的日期
};

#endif // GAMESCENE_H
