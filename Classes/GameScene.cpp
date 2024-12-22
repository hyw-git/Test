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
    GameTime::getInstance()->start(); // 启动游戏时间管理

    // 初始化社区系统（居民、节日等）
    initializeCommunity();

    // 启用每帧更新
    this->scheduleUpdate();

    return true;
}

void GameScene::initializeCommunity() {
    // 添加节日事件到社区系统
    communitySystem.addEvent(std::make_shared<Event>("Festival", "A special event to increase friendship.", "Day1", true));
    communitySystem.addEvent(std::make_shared<Event>("Market", "Residents exchange goods.", "Day2", false));
    communitySystem.addEvent(std::make_shared<Event>("Harvest Festival", "Celebrate the harvest.", "Day7", true));

    // 添加居民到社区系统
    auto alex = Resident::create("Alex", true); // 创建居民 Alex
    alex->setTexture("NPC/Alex.png");           // 设置 Alex 的头像
    communitySystem.addNPC(alex);               // 添加 Alex 到社区系统
    this->addChild(alex);                       // 将 Alex 添加到场景

    auto abigail = Resident::create("Abigail", true); // 创建居民 Abigail
    abigail->setTexture("NPC/Abigail.png");           // 设置 Abigail 的头像
    communitySystem.addNPC(abigail);                 // 添加 Abigail 到社区系统
    this->addChild(abigail);                         // 将 Abigail 添加到场景

    alex->offerTaskToPlayer(player);    // Alex 生成并提供任务
    abigail->offerTaskToPlayer(player); // Abigail 生成并提供任务
}

void GameScene::update(float dt) {
    // 更新游戏日程和事件
    updateGameDay();

    // 更新任务进度
    updateTaskProgress();
}

void GameScene::updateGameDay() {
    // 获取当前游戏时间
    auto gameTime = GameTime::getInstance();

    // 检查一天是否结束
    if (gameTime->isDayOver()) {
        CCLOG("一天结束，进入下一天...");
        gameTime->setNextDay(); // 进入下一天
    }

    // 触发新的一天的事件
    if (gameTime->hour == 6 && gameTime->minute == 0) {
        currentDate = getDayFromTime(); // 获取当前游戏日期
        communitySystem.triggerEventsForToday(currentDate); // 触发当天事件
    }
}

void GameScene::updateTaskProgress() {
    // 遍历所有居民，更新任务进度
    for (const auto& resident : communitySystem.getNPCs()) {
        for (const auto& task : resident->getTasks()) {
            task->updateProgress(1); // 每帧增加任务进度
            if (task->isCompleted()) {
                resident->completeTask(task); // 如果任务完成，处理奖励
            }
        }
    }
}

std::string GameScene::getDayFromTime() {
    // 将游戏时间映射为日期
    int dayIndex = GameTime::getInstance()->getCurrentDayIndex();
    switch (dayIndex % 7) { // 循环 7 天的周期
    case 0: return "Day1";
    case 1: return "Day2";
    case 2: return "Day3";
    case 3: return "Day4";
    case 4: return "Day5";
    case 5: return "Day6";
    case 6: return "Day7";
    default: return "Day1";
    }
}
