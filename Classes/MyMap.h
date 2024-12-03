#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"
USING_NS_CC;

class MyMap : public cocos2d::Scene
{
private:
    TMXTiledMap* mapTild;      //瓦片地图
    Sprite* _sprite;           //主角精灵
    Point spriteCurPos;        //主角当前在地图中的位置

public:
    static cocos2d::Scene* createMapScene();    //创建地图场景
    virtual bool init();                        //场景初始化

    //监听按下和松开键盘
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void CalcSite();                              //计算主角sprite当前位置
    void Move(EventKeyboard::KeyCode keyCode);    //控制主角sprite移动(WASD)


    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
