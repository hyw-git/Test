#include "Resident.h"
#include "CommunitySystem.h"
#include "GameTime.h"

Resident* Resident::create(const std::string& name, bool isSingle) {
    Resident* resident = new (std::nothrow) Resident();
    if (resident && resident->init(name, isSingle)) {
        resident->autorelease();
        return resident;
    }
    delete resident;
    return nullptr;
}

bool Resident::init(const std::string& name, bool isSingle) {
    if (!Node::init()) {
        return false;
    }

    this->name = name;
    this->isSingle = isSingle;
    this->friendshipPoints = 0;
    this->heartLevel = 0;
    this->heartEventTriggered = false;
    this->status = RelationshipStatus::FRIEND; // 初始化为普通朋友状态

    // 初始化任务模板
    taskTemplates.push_back(std::make_shared<Task>("收集石头", 100, 10, RewardType::Gold));
    taskTemplates.push_back(std::make_shared<Task>("修理工具", 150, 5, RewardType::Reputation));
    taskTemplates.push_back(std::make_shared<Task>("送货到居民", 200, 3, RewardType::Item));

    return true;
}

// 创建任务
std::shared_ptr<Task> Resident::createTask() {
    if (!taskTemplates.empty()) {
        int index = rand() % taskTemplates.size(); // 随机选择任务模板
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
        updateFriendship(reward); // 增加友好度
        CCLOG("%s 完成任务：%s，获得奖励：%d", name.c_str(), task->getDescription().c_str(), reward);
    }
}

// 更新友好度
void Resident::updateFriendship(int points) {
    friendshipPoints += points;

    // 限制友谊值上限（婚后为 3500，婚前为 2500）
    int maxFriendship = (status == RelationshipStatus::SPOUSE) ? 3500 : 2500;
    friendshipPoints = std::clamp(friendshipPoints, 0, maxFriendship);

    // 计算心等级（每 250 点对应 1 颗心）
    heartLevel = friendshipPoints / 250;

    CCLOG("%s 的友谊值更新为 %d 点（%d 颗心）。", name.c_str(), friendshipPoints, heartLevel);

    // 触发特殊事件（8 心时触发特殊剧情）
    if (heartLevel >= 8 && !heartEventTriggered) {
        heartEventTriggered = true;
        CCLOG("%s 的特殊剧情触发！", name.c_str());
    }
}

// 赠送花束（提升为恋爱关系）
bool Resident::offerBouquet() {
    if (heartLevel >= 8 && status == RelationshipStatus::FRIEND && isSingle) {
        status = RelationshipStatus::ROMANTIC; // 进入恋爱关系

        // 调用 PNG 图片展示
        auto bouquetSprite = cocos2d::Sprite::create("bouquet.png"); // 花束图片路径
        if (bouquetSprite) {
            bouquetSprite->setPosition(this->getPosition()); // 将花束图片放置在居民的位置
            this->getParent()->addChild(bouquetSprite);      
            bouquetSprite->runAction(cocos2d::Sequence::create(
                cocos2d::FadeOut::create(2.0f),              
                cocos2d::RemoveSelf::create(),              
                nullptr));
        }

        CCLOG("%s 接受了花束，现在处于恋爱关系。", name.c_str());
        return true;
    }
    CCLOG("%s 无法接受花束。", name.c_str());
    return false;
}

// 赠送美人鱼吊坠（结婚）
bool Resident::offerMermaidPendant() {
    if (heartLevel == 10 && status == RelationshipStatus::ROMANTIC) {
        status = RelationshipStatus::SPOUSE; // 成为配偶

        // 调用 PNG 图片展示
        auto pendantSprite = cocos2d::Sprite::create("Mermaid's_Pendant.png"); // 美人鱼吊坠图片路径
        if (pendantSprite) {
            pendantSprite->setPosition(this->getPosition()); // 将吊坠图片放置在居民的位置
            this->getParent()->addChild(pendantSprite);      
            pendantSprite->runAction(cocos2d::Sequence::create(
                cocos2d::ScaleTo::create(1.5f, 1.5f),        
                cocos2d::FadeOut::create(1.5f),             
                cocos2d::RemoveSelf::create(),              
                nullptr));
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
        friendshipChange = 80; // 喜爱礼物增加友好度
        break;
    case GiftPreference::LIKE:
        friendshipChange = 50; // 喜欢礼物增加友好度
        break;
    case GiftPreference::NEUTRAL:
        friendshipChange = 20; // 中立礼物增加少量友好度
        break;
    case GiftPreference::DISLIKE:
        friendshipChange = -20; // 不喜欢礼物减少友好度
        break;
    case GiftPreference::HATE:
        friendshipChange = -50; // 讨厌礼物减少大量友好度
        break;
    }

    updateFriendship(friendshipChange);
    CCLOG("%s 接受了礼物：%s，友好度变化：%d", name.c_str(), giftName.c_str(), friendshipChange);
}
void Resident::triggerRomanticEvent() {
    if (status == RelationshipStatus::ROMANTIC) {
        CCLOG("%s 与您开始浪漫约会！", name.c_str());
        updateFriendship(100); // 增加额外的友好度奖励
    }
    else {
        CCLOG("%s 当前不是您的恋人，无法触发浪漫事件。", name.c_str());
    }
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
            setPosition(schedule.location);
            CCLOG("%s 当前活动：%s", name.c_str(), schedule.activity.c_str());
            break;
        }
    }
}
