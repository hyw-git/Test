#ifndef __BAG_SCENE_H__
#define __BAG_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;

class Bag : public cocos2d::Scene
{
private:
    Character character;
public:
    Bag();
    static cocos2d::Scene* createScene();    //创建地图场景
    virtual bool init();                        //场景初始化
    void close(Ref* obj);

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(Bag);                           // implement the "static create()" method manually
};
#endif