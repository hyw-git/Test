#ifndef __ESC_SCENE_H__
#define __ESC_SCENE_H__

#include "cocos2d.h"

class Esc : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();         //��������
    virtual bool init();                          //������ʼ��
    void continueGame(Ref* obj);                  //��ʼ��ť
    void endGame(Ref* obj);                       //������ť
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Esc);
};

#endif
