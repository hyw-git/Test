#include "GameTime.h"

USING_NS_CC;

static GameTime* instance = nullptr;

// 单例实例
GameTime* GameTime::getInstance() {
    if (!instance) {
        instance = GameTime::create();
    }
    return instance;
}

// 初始化游戏时间
bool GameTime::init() {
    hour = 6;         // 游戏开始时间为早上 6 点
    minute = 0;       // 初始分钟为 0
    running = false;  // 时间流逝初始设置为停止
    timeSpeed = 0.7f; // 时间流速：现实 0.7 秒 = 游戏内 1 分钟
    return true;
}

// 开始时间流逝
void GameTime::start() {
    running = true;
    this->schedule(CC_SCHEDULE_SELECTOR(GameTime::updateTime), timeSpeed); // 按时间流速调用 updateTime
}

// 停止时间流逝
void GameTime::stop() {
    running = false;
    this->unschedule(CC_SCHEDULE_SELECTOR(GameTime::updateTime));
}

// 增加指定分钟数
void GameTime::addMinutes(int minutes) {
    minute += minutes;
    normalizeTime(); // 确保时间规范化
}

// 规范化时间：处理分钟数和小时数的溢出
void GameTime::normalizeTime() {
    if (minute >= 60) {
        minute -= 60;
        hour++;
    }
    if (hour >= 24) {
        hour = 0; // 如果小时超过 24，重置为 0
    }
}

// 获取格式化时间字符串
std::string GameTime::getFormattedTime() const {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute); // 格式化为 "HH:MM"
    return std::string(buffer);
}

// 判断当前时间段（白天、夜晚、午夜）
std::string GameTime::judgeTime() const {
    if (hour >= 6 && hour < 18) {
        return "day"; // 白天
    }
    else if (hour >= 18 && hour < 24) {
        return "night"; // 夜晚
    }
    else {
        return "midnight"; // 午夜
    }
}

// 检查一天是否结束（凌晨 2 点）
bool GameTime::isDayOver() const {
    return hour >= 2 && minute == 0; // 当时间到 2:00 AM 时返回 true
}

// 设置为第二天的早晨
void GameTime::setNextDay() {
    hour = 6;     // 早晨 6 点
    minute = 0;   // 分钟重置为 0
}

// 每帧更新时间
void GameTime::updateTime(float dt) {
    addMinutes(1); // 每次更新增加 1 分钟

    // 如果时间达到 2:00 AM，结束当前一天
    if (isDayOver()) {
        stop(); // 停止时间流逝
    }
}
