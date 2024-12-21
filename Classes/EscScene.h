#ifndef __ESC_SCENE_H__
#define __ESC_SCENE_H__

#include "cocos2d.h"

class Esc : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();         //创建场景
    virtual bool init();                          //场景初始化
    void continueGame(Ref* obj);                  //开始按钮
    void endGame(Ref* obj);                       //结束按钮
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Esc);
};

#endif
