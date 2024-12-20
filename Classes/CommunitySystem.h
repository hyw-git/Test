#ifndef COMMUNITYSYSTEM_H
#define COMMUNITYSYSTEM_H

#include "Resident.h"
#include "Event.h"
#include <vector>
#include <string>

class CommunitySystem {
public:
    void addNPC(Resident* resident);              // 添加居民
    void interactWithAllResidents();               // 与所有居民交互
    void assignTaskToResident(Resident* resident, Task* task);  // 给居民分配任务
    void triggerFestival();                         // 触发节日活动
    void addEvent(Event* event);                   // 添加节日活动
    void triggerEventsForToday(const std::string& currentDate);  // 根据当前日期触发事件

private:
    std::vector<Resident*> npcs;                   // 存储居民
    std::vector<Event*> events;                    // 存储节日活动
};

#endif // COMMUNITYSYSTEM_H
