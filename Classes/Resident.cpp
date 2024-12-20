#include "Resident.h"
#include "cocos2d.h"

USING_NS_CC;

Resident* Resident::create(const std::string& name, bool isSingle) {
    Resident* resident = new (std::nothrow) Resident();
    if (resident && resident->init(name, isSingle)) {
        resident->autorelease();
        return resident
    }
    delete resident;
    return nullptr
}

bool Resident::init(const std::string& name, bool isSingle) {
    this->name = name;
    this->isSingle = isSingle;
    this->friendshipPoints = 0;
    this->heartLevel = 0;
    this->heartEventTriggered = false;
    this->weeklyGiftCount = 0;
    this->inRomanticRelationship = false;

    return true
}

void Resident::assignTask(Task* task) {
    tasks.push_back(task);
    CCLOG("%s 分配了任务：%s", name.c_str(), task->getDescription().c_str())
}

void Resident::completeTask(Task* task) {
    if (task->isCompleted()) {
        int reward = task->getReward();
        friendshipPoints += reward;  // 完成任务后增加友谊值
        heartLevel = friendshipPoints / 250;
        CCLOG("%s 完成了任务：%s，获得了 %d 友谊值！", name.c_str(), task->getDescription().c_str(), reward)
    }
}

void Resident::interact() {
    CCLOG("%s: 与你交谈！", name.c_str())
}

void Resident::giveGift(const std::string& giftType) {
    CCLOG("赠送礼物给 %s", name.c_str())
}

void Resident::updateFriendship(int points) {
    friendshipPoints += points;
    heartLevel = friendshipPoints / 250
}

int Resident::getFriendshipPoints() const {
    return friendshipPoints
}

int Resident::getHeartLevel() const {
    return heartLevel
}

bool Resident::canRomance() const {
    return isSingle && heartLevel >= 8
}

bool Resident::canMarry() const {
    return isSingle && heartLevel >= 10
}
