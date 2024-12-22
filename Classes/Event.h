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

// 完成任务
void Resident::completeTask(std::shared_ptr<Task> task) {
    if (task->isCompleted()) {
        int reward = task->getReward();
        updateFriendship(reward);
        CCLOG("%s 完成任务：%s", name.c_str(), task->getDescription().c_str());
    }
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

// 赠送花束
bool Resident::offerBouquet() {
    if (heartLevel >= 8 && status == RelationshipStatus::FRIEND) {
        status = RelationshipStatus::ROMANTIC; // 进入恋爱关系

        auto bouquetSprite = cocos2d::Sprite::create("bouquet.png");
        if (bouquetSprite) {
            CCLOG("花束图片加载成功！");
        }

        CCLOG("%s 接受了花束，现在处于恋爱关系。", name.c_str());
        return true;
    }
    CCLOG("%s 无法接受花束。", name.c_str());
    return false;
}

// 赠送美人鱼吊坠
bool Resident::offerMermaidPendant() {
    if (heartLevel == 10 && status == RelationshipStatus::ROMANTIC) {
        status = RelationshipStatus::SPOUSE; // 成为配偶

        auto pendantSprite = cocos2d::Sprite::create("Mermaid's_Pendant.png");
        if (pendantSprite) {
            CCLOG("美人鱼吊坠图片加载成功！");
        }

        CCLOG("%s 接受了美人鱼吊坠并与你结婚！", name.c_str());
        return true;
    }
    CCLOG("%s 无法接受美人鱼吊坠。", name.c_str());
    return false;
}

// 查询是否处于恋爱关系
bool Resident::isRomantic() const {
    return status == RelationshipStatus::ROMANTIC;
}

// 查询是否已结婚
bool Resident::isSpouse() const {
    return status == RelationshipStatus::SPOUSE;
}

// 接受礼物
void Resident::acceptGift(const std::string& giftName, GiftPreference preference) {
    int friendshipChange = 0;

    switch (preference) {
    case GiftPreference::LOVE:
        friendshipChange = 80;
        break;
    case GiftPreference::LIKE:
        friendshipChange = 50;
        break;
    case GiftPreference::NEUTRAL:
        friendshipChange = 20;
        break;
    case GiftPreference::DISLIKE:
        friendshipChange = -20;
        break;
    case GiftPreference::HATE:
        friendshipChange = -50;
        break;
    }

    updateFriendship(friendshipChange);
    CCLOG("%s 接受了礼物：%s，友好度变化：%d", name.c_str(), giftName.c_str(), friendshipChange);
}

// 参与节日
void Resident::participateInFestival(const std::string& festivalName) {
    updateFriendship(100); // 增加节日参与奖励
    CCLOG("%s 正在参与节日：%s", name.c_str(), festivalName.c_str());
}

// 更新居民日程
void Resident::updateSchedule(int currentHour) {
    for (const auto& schedule : dailySchedule) {
        if (currentHour >= schedule.startHour && currentHour < schedule.endHour) {
            CCLOG("%s 当前活动：%s", name.c_str(), schedule.activity.c_str());
            break;
        }
    }
}

void Resident::addGold(int gold) {
    Gold += gold;
}

void Resident::addReputation(int reputation) {
    Reputation += reputation;
}
