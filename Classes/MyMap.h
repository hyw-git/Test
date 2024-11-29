#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"
USING_NS_CC;


class MyMap : public cocos2d::Scene
{
private:

//��ס�����¼����õ��ĳ�Ա
#if 0
    int frameIndex;
    int nextKeyFrameIndex;
#endif

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    TMXTiledMap* mapTild;      //��Ƭ��ͼ
    Sprite* _sprite;           //���Ǿ���


public:
    static cocos2d::Scene* createMapScene();
    virtual bool init();

//���º��ɿ�����
#if 1
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif


//ʶ��ס�����¼�����غ����������޸�
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
