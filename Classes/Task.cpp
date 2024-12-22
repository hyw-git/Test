#include "Task.h"
#include "Resident.h"
#include "cocos2d.h"

using namespace cocos2d;

// 创建一个任务实例
std::shared_ptr<Task> Task::create(const std::string& description, int reward, int requiredCount, RewardType rewardType) {
    return std::make_shared<Task>(description, reward, requiredCount, rewardType);
}

// 任务类的构造函数
Task::Task(const std::string& description, int reward, int requiredCount, RewardType rewardType)
    : _description(description),            // 初始化任务描述
    _reward(reward),                      // 初始化任务奖励数值
    _requiredCount(requiredCount),        // 初始化任务完成所需的目标数量
    _currentProgress(0),                  // 初始化当前完成进度为 0
    _rewardType(rewardType) {             // 初始化奖励类型
}

// 更新任务进度
void Task::updateProgress(int progress) {
    _currentProgress += progress;           // 增加当前进度
    if (_currentProgress > _requiredCount) { // 如果进度超过所需数量
        _currentProgress = _requiredCount;  // 将进度调整为最大值
    }
}

// 检查任务是否完成
bool Task::isCompleted() const {
    return _currentProgress >= _requiredCount; // 当前进度达到或超过需求数量
}

// 完成任务的逻辑
void Task::completeTask(Resident* resident) {
    if (isCompleted()) { // 检查任务是否完成
        // 根据奖励类型给予居民相应的奖励
        if (_rewardType == RewardType::Gold) {
            resident->addGold(_reward);    // 增加金币奖励
        }
        else if (_rewardType == RewardType::Reputation) {
            resident->addReputation(_reward); // 增加声望奖励
        }
        CCLOG("任务完成！奖励：%d", _reward);
    }
}

// 获取任务的描述信息
std::string Task::getDescription() const {
    return _description;
}

// 获取任务的奖励类型
RewardType Task::getRewardType() const {
    return _rewardType;
}
