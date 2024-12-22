#include "CommunitySystem.h"
#include "GameTime.h"

static CommunitySystem* instance = nullptr;

// 单例模式获取实例
CommunitySystem* CommunitySystem::getInstance() {
    if (!instance) {
        instance = new CommunitySystem();
        instance->initializeFestivals();
        instance->initializeTaskTemplates();
    }
    return instance;
}

// 更新所有居民的状态
void CommunitySystem::updateAllResidents() {
    int currentHour = GameTime::getInstance()->getCurrentHour();

    for (auto& resident : residents) {
        resident->updateSchedule(currentHour);

        // 自动检查并更新任务状态
        resident->updateTaskProgress();
    }
}

// 检查并触发节日
void CommunitySystem::checkAndTriggerFestivals(const std::string& currentSeason, int currentDay) {
    if (currentFestival) return; // 如果已经有节日进行中，则直接返回

    for (const auto& festival : festivals) {
        if (festival.season == currentSeason && festival.day == currentDay) {
            currentFestival = std::make_shared<Festival>(festival);

            // 通知所有居民参与节日
            for (auto& resident : residents) {
                resident->participateInFestival(currentFestival->name);
            }

            CCLOG("节日 %s 开始了！", currentFestival->name.c_str());
            break;
        }
    }
}

// 生成每日任务（按需创建）
void CommunitySystem::generateDailyTasks() {
    availableTasks.clear();

    // 遍历居民，根据需求生成任务
    for (const auto& resident : residents) {
        auto task = resident->createTask();
        if (task) {
            availableTasks.push_back(task);
        }
    }
}

// 分配任务
void CommunitySystem::assignRandomTask(std::shared_ptr<Resident> resident) {
    if (availableTasks.empty()) {
        generateDailyTasks(); // 如果没有任务可用，则生成每日任务
    }

    if (!availableTasks.empty()) {
        int index = rand() % availableTasks.size();
        auto task = availableTasks[index];
        resident->assignTask(task);
        availableTasks.erase(availableTasks.begin() + index); // 移除已分配任务
    }
}
