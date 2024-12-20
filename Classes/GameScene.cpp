#include "GameScene.h"
#include "Event.h"
#include "CommunitySystem.h"
#include "Task.h"
#include "GameTime.h"
#include "cocos2d.h"

USING_NS_CC;

GameScene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 初始化游戏时间
    GameTime::getInstance()->start(); // 开始时间流逝

    // 添加节日事件到社区系统
    Event* festival = new Event("Festival", "A special event to increase friendship.", "Day1", true);
    communitySystem.addEvent(festival);

    Event* market = new Event("Market", "Residents exchange goods.", "Day2", false);
    communitySystem.addEvent(market);

    // 添加居民到社区系统
    Resident* resident1 = Resident::create("Resident1", true);  // 示例居民1
    Resident* resident2 = Resident::create("Resident2", false); // 示例居民2
    communitySystem.addNPC(resident1);
    communitySystem.addNPC(resident2);

    // 创建任务并分配给居民
    Task* task = new Task("Generic Task", 100, 10); // 示例任务：收集10个物品
    communitySystem.assignTaskToResident(resident1, task);

    // 将居民添加到场景
    this->addChild(resident1);
    this->addChild(resident2);

    // 与所有居民进行交互
    communitySystem.interactWithAllResidents();

    // 如果有节日活动，触发节日事件
    communitySystem.triggerFestival();

    // 启用每帧更新
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
    // 获取当前游戏时间
    GameTime* gameTime = GameTime::getInstance();
    std::string formattedTime = gameTime->getFormattedTime(); // 获取当前时间字符串（如 "06:00"）

    // 检查一天是否结束
    if (gameTime->isDayOver()) {
        CCLOG("Day over! Setting to next day...");
        gameTime->setNextDay(); // 设置为第二天的早晨 6 点
    }

    // 在新的一天开始时触发事件
    if (gameTime->hour == 6 && gameTime->minute == 0) { // 检查是否为新的一天
        std::string currentDay = getDayFromTime(); // 根据时间映射获取当前游戏中的日期
        communitySystem.triggerEventsForToday(currentDay); // 触发当天的事件
    }

    // 模拟物品收集和任务进度更新
    for (auto& resident : communitySystem.getNPCs()) {
        for (auto& task : resident->getTasks()) {
            task->updateProgress(1); // 增加任务进度，每次增加 1
            if (task->isCompleted()) {
                resident->completeTask(task); // 如果任务完成，触发奖励逻辑
            }
        }
    }
}

// 帮助函数：根据时间获取对应的游戏日
std::string GameScene::getDayFromTime() {
    int dayIndex = GameTime::getInstance()->hour / 6; // 将每 6 小时映射为一天的周期
    switch (dayIndex) {
    case 0: return "Day1";
    case 1: return "Day2";
    case 2: return "Day3";
    default: return "Day1"; // 默认返回 Day1
    }
}
