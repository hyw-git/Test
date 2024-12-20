#include "CommunitySystem.h"
#include "Resident.h"
#include "cocos2d.h"

void CommunitySystem::addNPC(Resident* resident) {
    npcs.push_back(resident); // 将居民添加到系统中
}

void CommunitySystem::interactWithAllResidents() {
    for (auto resident : npcs) {
        resident->interact(); // 与所有居民进行交互
    }
}

void CommunitySystem::triggerFestival() {
    for (auto resident : npcs) {
        resident->updateFriendship(20); // 节日活动增加友谊值
    }
}

void CommunitySystem::addEvent(Event* event) {
    events.push_back(event); // 添加节日活动
}

void CommunitySystem::triggerEventsForToday(const std::string& currentDate) {
    for (auto event : events) {
        if (event->getDate() == currentDate) {
            event->triggerEvent(); // 触发今天的活动
        }
    }
}

void CommunitySystem::assignTaskToResident(Resident* resident, Task* task) {
    resident->assignTask(task); // 给居民分配任务
}
