#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    Task(const std::string& description, int reward, int requiredCount);

    void updateProgress(int progress);  // 更新任务进度
    bool isCompleted() const;          // 检查任务是否完成
    int getReward() const;             // 获取任务奖励
    std::string getDescription() const; // 获取任务描述

private:
    std::string description;  // 任务描述
    int reward;               // 任务奖励（例如金币、友谊值等）
    int requiredCount;        // 任务需要完成的数量
    int currentProgress;      // 当前完成进度
};

#endif // TASK_H
