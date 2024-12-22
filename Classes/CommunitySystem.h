#ifndef COMMUNITYSYSTEM_H
#define COMMUNITYSYSTEM_H

#include "Resident.h"
#include "Event.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

// 节日信息结构
struct Festival {
    std::string name;                   // 节日名称
    std::string season;                 // 节日所在季节
    int day;                            // 节日日期
    std::string description;            // 节日描述
    std::vector<std::string> activities; // 节日的活动列表
    bool isActive = false;              // 是否正在进行中
};

class CommunitySystem {
public:
    static CommunitySystem* getInstance();

    void addResident(std::shared_ptr<Resident> resident);
    void removeResident(std::shared_ptr<Resident> resident);
    void updateAllResidents();

    // 节日系统
    void addFestival(const Festival& festival);
    void checkAndTriggerFestivals(const std::string& currentSeason, int currentDay);
    void endCurrentFestival();

    // 任务系统
    void generateDailyTasks();
    void assignRandomTask(std::shared_ptr<Resident> resident);
    void completeTask(std::shared_ptr<Resident> resident, std::shared_ptr<Task> task);

    // 社交系统
    void updateRelationships();
    void triggerRandomEvents();
    std::vector<std::shared_ptr<Resident>> getAvailableResidents() const;

private:
    CommunitySystem(); // 私有构造函数，单例模式
    void initializeFestivals();
    void initializeTaskTemplates();
    bool isFestivalDay(const std::string& season, int day) const;

    std::vector<std::shared_ptr<Resident>> residents;  // 社区居民列表
    std::vector<Festival> festivals;                  // 节日信息列表
    std::shared_ptr<Festival> currentFestival;        // 当前正在进行的节日
    std::vector<std::shared_ptr<Task>> availableTasks; // 可用任务列表
};

#endif // COMMUNITYSYSTEM_H
