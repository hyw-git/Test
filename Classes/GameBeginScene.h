#ifndef __GAMEBEGIN_SCENE_H__
#define __GAMEBEGIN_SCENE_H__

#include "cocos2d.h"

class GameBegin : public cocos2d::Scene
{ 
public:
    static cocos2d::Scene* createScene();    //��������
    virtual bool init();                     //������ʼ��
    void startGame(Ref* obj);                //��ʼ��ť
    void endGame(Ref* obj);                  //������ť
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameBegin);
};

#endif // __HELLOWORLD_SCENE_H__
