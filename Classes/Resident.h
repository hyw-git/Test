#ifndef RESIDENT_H
#define RESIDENT_H

#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
#include "Task.h"

class Resident : public cocos2d::Node {
public:
    static Resident* create(const std::string& name, bool isSingle);

    virtual bool init(const std::string& name, bool isSingle);

    // 社交功能
    void interact();                                 // 与居民交谈
    void giveGift(const std::string& giftType);      // 赠送礼物
    void updateFriendship(int points);              // 更新友谊值
    void reduceFriendship(int points);              // 减少友谊值
    void triggerHeartEvent();                       // 解锁爱心事件

    // 任务功能
    void assignTask(Task* task);                    // 给居民分配任务
    void completeTask(Task* task);                  // 玩家完成任务，居民给予奖励
    void showTasks() const;                         // 显示当前任务列表
    bool hasPendingTasks() const;                   // 检查是否有未完成的任务

    // 行为功能
    void updateBehavior(int hour);                  // 根据时间更新行为
    void moveToLocation(const cocos2d::Vec2& position); // 移动到指定位置

    // 获取状态
    int getFriendshipPoints() const;                // 当前友谊值
    int getHeartLevel() const;                      // 爱心等级
    bool canRomance() const;                        // 是否可以发展浪漫关系
    bool canMarry() const;                          // 是否可以结婚

    CREATE_FUNC(Resident);

private:
    std::string name;                               // 居民名称
    bool isSingle;                                  // 是否为单身居民
    int friendshipPoints;                           // 友谊值
    int heartLevel;                                 // 爱心等级
    bool heartEventTriggered;                       // 是否触发爱心事件
    std::map<std::string, int> giftPreferences;     // 礼物偏好表
    int weeklyGiftCount;                            // 每周礼物计数
    bool inRomanticRelationship;                    // 是否处于浪漫关系
    std::vector<Task*> tasks;                       // 居民的任务列表
};

#endif // RESIDENT_H
