#ifndef EVENT_H
#define EVENT_H

#include "cocos2d.h"
#include <string>
#include <functional>

enum class EventType {
    TIME_TRIGGER,    // 时间触发事件
    NPC_INTERACTION, // NPC交互事件
    SCENE_CHANGE,    // 场景切换事件
    LOVE_EVENT,      // 恋爱事件
    CUSTOM           // 自定义事件
};

// Event 类（继承 cocos2d::Ref）
class Event : public cocos2d::Ref {
private:
    std::string _eventId;                  // 事件唯一ID
    EventType _type;                       // 事件类型
    std::function<void()> _callback;       // 回调函数
    float _triggerTime;                    // 触发时间（针对时间触发事件）
    bool _isRecurring;                     // 是否是循环事件

public:
    // 构造函数
    Event(const std::string& id, EventType type, std::function<void()> callback, float triggerTime = -1.0f, bool isRecurring = false)
        : _eventId(id), _type(type), _callback(callback), _triggerTime(triggerTime), _isRecurring(isRecurring) {
    }

    // 静态创建函数
    static Event* create(const std::string& id, EventType type, std::function<void()> callback, float triggerTime = -1.0f, bool isRecurring = false) {
        Event* event = new Event(id, type, callback, triggerTime, isRecurring);
        if (event) {
            event->autorelease();
            return event;
        }
        CC_SAFE_DELETE(event);
        return nullptr;
    }

    // 获取事件ID
    const std::string& getId() const { return _eventId; }

    // 获取事件类型
    EventType getType() const { return _type; }

    // 获取触发时间
    float getTriggerTime() const { return _triggerTime; }

    // 判断是否为循环事件
    bool isRecurring() const { return _isRecurring; }

    // 执行事件
    void execute() {
        if (_callback) {
            _callback();
        }
    }
};

// EventManager 类
class EventManager : public cocos2d::Ref {
private:
    cocos2d::Map<std::string, Event*> _events; // 用 Map 存储所有事件

public:
    // 静态创建函数
    static EventManager* create() {
        EventManager* manager = new EventManager();
        if (manager) {
            manager->autorelease();
            return manager;
        }
        CC_SAFE_DELETE(manager);
        return nullptr;
    }

    // 添加事件
    void addEvent(Event* event) {
        if (event) {
            _events.insert(event->getId(), event);
        }
    }

    // 移除事件
    void removeEvent(const std::string& id) {
        _events.erase(id);
    }

    // 手动触发事件
    void triggerEvent(const std::string& id) {
        if (_events.find(id) != _events.end()) {
            _events.at(id)->execute();
        }
    }

    // 根据时间触发事件
    void triggerTimeEvents(float currentTime) {
        auto keysToRemove = cocos2d::Vector<std::string>();
        for (const auto& pair : _events) {
            Event* event = pair.second;
            if (event->getType() == EventType::TIME_TRIGGER && event->getTriggerTime() <= currentTime) {
                event->execute();
                if (!event->isRecurring()) {
                    keysToRemove.pushBack(pair.first);
                }
            }
        }

        // 移除非循环事件
        for (const auto& key : keysToRemove) {
            _events.erase(key);
        }
    }
};

#endif // EVENT_H
