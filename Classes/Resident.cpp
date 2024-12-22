#include "Resident.h"
#include "CommunitySystem.h"
#include "GameTime.h"

Resident* Resident::create(const std::string& name, bool isMarriable) {
    Resident* resident = new (std::nothrow) Resident();
    if (resident && resident->init(name, isMarriable)) {
        resident->autorelease();
        return resident;
    }
    delete resident;
    return nullptr;
}
const std::vector<std::shared_ptr<Task>>& Resident::getTasks() const {
    return assignedTasks;

bool Resident::init(const std::string& name, bool isMarriable) {
    if (!Node::init()) {
        return false;
    }

    this->name = name;
    this->isMarriable = isMarriable;
    this->friendshipPoints = 0;
    this->heartLevel = 0;
    this->heartEventTriggered = false;
    this->status = RelationshipStatus::FRIEND;
    this->Gold = 0;
    this->Reputation = 0;

    taskTemplates.push_back(std::make_shared<Task>("收集石头", 100, 10, RewardType::Gold));
    taskTemplates.push_back(std::make_shared<Task>("修理工具", 150, 5, RewardType::Reputation));
    taskTemplates.push_back(std::make_shared<Task>("送货到居民", 200, 3, RewardType::Item));

    return true;
}

// 创建任务
std::shared_ptr<Task> Resident::createTask() {
    if (!taskTemplates.empty()) {
        int index = rand() % taskTemplates.size();
        return taskTemplates[index];
    }
    return nullptr;
}

// 提供任务到任务系统
void Resident::offerTaskToSystem(CommunitySystem* system) {
    auto task = createTask();
    if (task) {
        system->addTask(task);
        CCLOG("%s 提供了任务：%s", name.c_str(), task->getDescription().c_str());
    }
    else {
        CCLOG("%s 没有可用任务提供", name.c_str());
    }
}
void Resident::updateTaskProgress() {
    for (const auto& task : assignedTasks) { 
        if (!task->isCompleted()) {
            task->updateProgress(1); 
            if (task->isCompleted()) {
                completeTask(task); 
            }
        }
    }
}

// 完成任务
void Resident::completeTask(std::shared_ptr<Task> task) {
    if (task->isCompleted()) {
        updateFriendship(task->getReward());
        CCLOG("%s 完成任务：%s", name.c_str(), task->getDescription().c_str());
    }
}
void Resident::participateInFestival(const std::string& festivalName) {
    updateFriendship(100); // 增加节日参与奖励
    CCLOG("%s 正在参与节日：%s", name.c_str(), festivalName.c_str());
}


// 更新友好度
void Resident::updateFriendship(int points) {
    friendshipPoints += points;
    int maxFriendship = (status == RelationshipStatus::SPOUSE) ? 3500 : 2500;
    friendshipPoints = std::max(0, std::min(friendshipPoints, maxFriendship));
    heartLevel = friendshipPoints / 250;

    if (heartLevel >= 8 && !heartEventTriggered) {
        heartEventTriggered = true;
        CCLOG("%s 的特殊剧情触发！", name.c_str());
    }
}
