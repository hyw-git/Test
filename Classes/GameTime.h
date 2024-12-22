#ifndef GAMETIME_H
#define GAMETIME_H

#include "cocos2d.h"
#include <string>

class GameTime : public cocos2d::Node {
public:
    // 获取单例实例
    static GameTime* getInstance();

    // 初始化方法
    virtual bool init();

    // 时间控制方法
    void start();                            // 开始时间流逝
    void stop();                             // 停止时间流逝
    void addMinutes(int minutes);            // 增加游戏时间
    void setNextDay();                       // 跳转到第二天

    // 时间获取方法
    int getCurrentHour() const;              // 获取当前小时
    int getCurrentMinute() const;            // 获取当前分钟
    std::string getFormattedTime() const;    // 获取格式化时间（如 "06:30"）
    std::string judgeTime() const;           // 判断当前时间段（如早晨、下午）
    bool isDayOver() const;                  // 判断是否为凌晨 2 点

    CREATE_FUNC(GameTime);                 

private:
    // 私有构造函数，防止外部创建
    GameTime() : hour(6), minute(0), running(false), timeSpeed(0.7f) {}

    // 成员变量
    int hour;                                // 当前小时（0-23）
    int minute;                              // 当前分钟（0-59）
    bool running;                            // 时间是否在流逝
    float timeSpeed;                         // 时间流逝速度（现实 0.7 秒 = 游戏 1 分钟）

    // 内部方法
    void normalizeTime();                    // 校正时间（分钟进位、小时重置）
    void updateTime(float dt);               // 按时间流速更新时间
};

#endif // GAMETIME_H
