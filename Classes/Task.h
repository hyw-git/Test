#ifndef TASK_H
#define TASK_H

#include <string>
#include <memory>
#include "Resident.h"

// 前向声明 Resident
class Resident;

enum class RewardType { Gold, Reputation, Item }; // 奖励类型

class Task {
public:
    // 使用智能指针管理任务对象
    static std::shared_ptr<Task> create(const std::string& description, int reward, int requiredCount, RewardType rewardType);

    void updateProgress(int progress);  // 更新任务进度
    bool isCompleted() const;          // 检查任务是否完成
    void completeTask(Resident* resident); // 完成任务
    std::string getDescription() const; // 获取任务描述
    RewardType getRewardType() const;  // 获取奖励类型
    int getReward() const;             // 获取奖励数值

private:
    // 创建对象
    Task(const std::string& description, int reward, int requiredCount, RewardType rewardType);

    std::string _description;          // 任务描述
    int _reward;                       // 奖励数值
    int _requiredCount;                // 任务完成所需数量
    int _currentProgress;              // 当前任务进度
    RewardType _rewardType;            // 奖励类型
};

#endif // TASK_H
