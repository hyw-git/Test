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
    static cocos2d::Scene* createScene();    //������ͼ����
    virtual bool init();                        //������ʼ��
    void close(Ref* obj);

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(Bag);                           // implement the "static create()" method manually
};
#endif