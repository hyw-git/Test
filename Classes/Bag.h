#ifndef __BAG_SCENE_H__
#define __BAG_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;

class Bag : public cocos2d::Scene
{
private:
    Character& character = Character::getInstance(); //单例主角
public:
    static cocos2d::Scene* createScene();            //创建地图场景
    virtual bool init();                             //场景初始化
    void close(Ref* obj);                            //关闭背包

    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Bag);
};
#endif