#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "CommunitySystem.h"

class GameScene : public cocos2d::Scene {
public:
    static GameScene* createScene();
    virtual bool init();
    void update(float dt); 

    CREATE_FUNC(GameScene);

private:
    CommunitySystem communitySystem; // 管理社交系统
    std::string getDayFromTime(); // 根据时间获取当前游戏中的日期
    std::string currentDate;         // 当前日期
};

#endif // GAMESCENE_H
