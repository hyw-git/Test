#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "EscScene.h"
#include "Bag.h"

USING_NS_CC;

class Room : public cocos2d::Scene
{
private:
    Character& character = Character::getInstance();  //����
    TMXTiledMap* mapTild;                             //��Ƭ��ͼ
    Sprite* _sprite;                                  //���Ǿ���
    Point spriteCurPos;                               //���ǵ�ǰ�ڵ�ͼ�е�λ��
    float speed;

    //�ƶ�����¼
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;

    //�ܶ�������¼
    bool run_A;
    bool run_D;
    bool run_W;
    bool run_S;

public:
    Room();                                          //Ĭ�Ϲ��캯��
    static cocos2d::Scene* createMapScene();         //������ͼ����
    virtual bool init();                             //������ʼ��

    void update(float deltaTime);                    //֡����ƶ�

    //�������º��ɿ�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void CalcSite();                              //��������sprite��ǰλ��
    void Esc();                                   //esc���˳�
    void bag();

    void Ani_A();                                //����֡����
    void Ani_D();                                //����֡����
    void Ani_W();                                //����֡����
    void Ani_S();                                //����֡����

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(Room);                           // implement the "static create()" method manually
};
#endif