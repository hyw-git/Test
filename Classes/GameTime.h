#ifndef GAMETIME_H
#define GAMETIME_H

#include "cocos2d.h"
#include <string>

class GameTime : public cocos2d::Node {
public:
    static GameTime* getInstance();          // 单例模式
    virtual bool init();                     // 初始化
    void start();                            // 开始时间流逝
    void stop();                             // 停止时间流逝
    void addMinutes(int minutes);            // 增加游戏时间
    std::string getFormattedTime() const;    // 获取格式化的时间
    std::string judgeTime() const;           // 判断当前时间段（白天、夜晚、凌晨）
    bool isDayOver() const;                  // 判断是否凌晨2点

    void setNextDay();                       // 跳转到第二天
    int getCurrentHour() const { return hour; }
    int getCurrentMinute() const { return minute; }

    CREATE_FUNC(GameTime);

private:
    int hour;        // 当前小时
    int minute;      // 当前分钟
    bool running;    // 时间是否在流逝
    float timeSpeed; // 时间流速（现实 0.7 秒 = 游戏内 1 分钟）

    void normalizeTime(); // 校正时间
    void updateTime(float dt); // 更新时间
};

#endif // GAMETIME_H
