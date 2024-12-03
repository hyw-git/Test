#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"
USING_NS_CC;

class MyMap : public cocos2d::Scene
{
private:
    TMXTiledMap* mapTild;      //��Ƭ��ͼ
    Sprite* _sprite;           //���Ǿ���
    Point spriteCurPos;        //���ǵ�ǰ�ڵ�ͼ�е�λ��

public:
    static cocos2d::Scene* createMapScene();    //������ͼ����
    virtual bool init();                        //������ʼ��

    //�������º��ɿ�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void CalcSite();                              //��������sprite��ǰλ��
    void Move(EventKeyboard::KeyCode keyCode);    //��������sprite�ƶ�(WASD)


    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
