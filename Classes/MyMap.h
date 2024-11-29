#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"
USING_NS_CC;


class MyMap : public cocos2d::Scene
{
private:

//按住键盘事件会用到的成员
#if 0
    int frameIndex;
    int nextKeyFrameIndex;
#endif

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    TMXTiledMap* mapTild;      //瓦片地图
    Sprite* _sprite;           //主角精灵


public:
    static cocos2d::Scene* createMapScene();
    virtual bool init();

//按下和松开键盘
#if 1
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif


//识别按住键盘事件的相关函数待测试修改
#if 0
    virtual void update(float dt);
    bool isKeyPressed(EventKeyboard::KeyCode keyCode);
    void keyPressedDuration(EventKeyboard::KeyCode keyCode);
    void resetTimer();
#endif

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyMap);
};

#endif // __HELLOWORLD_SCENE_H__
