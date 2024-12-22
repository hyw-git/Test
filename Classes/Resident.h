#ifndef RESIDENT_H
#define RESIDENT_H

#include "cocos2d.h"
#include "Task.h"
#include <string>
#include <vector>
#include <memory>

// 礼物偏好
enum class GiftPreference {
    LOVE, LIKE, NEUTRAL, DISLIKE, HATE
};

// 恋爱和婚姻状态
enum class RelationshipStatus {
    FRIEND,    // 普通朋友
    ROMANTIC,  // 恋爱关系
    SPOUSE     // 配偶
};

// 居民日程安排
struct Schedule {
    cocos2d::Vec2 location; // 活动位置
    int startHour;          // 开始时间
    int endHour;            // 结束时间
    std::string activity;   // 活动内容
};

class CommunitySystem;

class Resident : public cocos2d::Node {
public:
    static Resident* create(const std::string& name, bool isMarriable);
    virtual bool init(const std::string& name, bool isMarriable);

    // 任务相关
    std::shared_ptr<Task> createTask();               // 创建任务
    void offerTaskToSystem(CommunitySystem* system); // 提供任务到任务系统
    void completeTask(std::shared_ptr<Task> task);   // 完成任务
    void updateTaskProgress(); // 更新任务进度
    void assignTask(std::shared_ptr<Task> task); // 分配任务


    // 社交相关
    void participateInFestival(const std::string& festivalName);// 参与节日
    void updateFriendship(int points);                          // 更新友好度
    bool offerBouquet();                                         // 赠送花束
    bool offerMermaidPendant();                                  // 赠送美人鱼吊坠（结婚）
    void triggerRomanticEvent();                                // 触发浪漫事件

    // 状态查询
    bool isRomantic() const;                         // 是否处于恋爱关系
    bool isSpouse() const;                           // 是否已结婚
    int getFriendshipPoints() const;                 // 获取当前友谊值
    int getHeartLevel() const;                       // 获取心等级

    void addGold(int gold);
    void addReputation(int reputation);
    void setTexture(std::string);

    // 日程相关
    void updateSchedule(int currentHour); // 更新居民日程
    // 礼物相关
    void acceptGift(const std::string& giftName, GiftPreference preference);

    const std::vector<std::shared_ptr<Task>>& getTasks() const; // 获取分配的任务
private:
    std::string name; // 居民姓名
    bool isMarriable; // 是否可结婚
    int friendshipPoints; // 好感度
    int heartLevel;       // 心等级
    RelationshipStatus status; // 当前关系状态
    bool heartEventTriggered;  // 是否触发特殊剧情
    int Gold;                  // 当前金币数量
    int Reputation;            // 当前声望值

    std::vector<std::shared_ptr<Task>> taskTemplates; // 任务模板
    std::vector<std::shared_ptr<Task>> assignedTasks; // 存储分配给居民的任务
    std::vector<Schedule> dailySchedule;             // 日程安排
};


#endif // RESIDENT_H
