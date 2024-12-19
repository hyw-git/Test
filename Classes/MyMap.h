#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"

#include "EscScene.h"
#include "RoomScene.h"

USING_NS_CC;

class MyMap : public cocos2d::Scene
{
private:
    Character character;
    TMXTiledMap* mapTild;      //��Ƭ��ͼ
    Sprite* _sprite;           //���Ǿ���
    Point spriteCurPos;        //���ǵ�ǰ�ڵ�ͼ�е�λ��
    Point spriteNextPos;

    //��¼ׯ������
    std::vector<float> cropX;
    std::vector<float> cropY;

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
    MyMap();                                    //Ĭ�Ϲ��캯��
    static cocos2d::Scene* createMapScene();    //������ͼ����
    virtual bool init();                        //������ʼ��

    void update(float deltaTime);               //֡����ƶ�

    //�������º��ɿ�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void CalcSite();                              //��������sprite��ǰλ��

    //���ð�ť
    void Set(Ref* obj);  //���ղ˵���ť��
    void Change_Hoe(Ref* obj);
    void Change_Seed(Ref* obj);
    void Change_Sickle(Ref* obj);
    void Esc();    //esc���˳�
    void Bag();
    void Room();

    void onCropMature(float dt);  //��������
    void Ani_A();  //����֡����
    void Ani_D();  //����֡����
    void Ani_W();  //����֡����
    void Ani_S();  //����֡����

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
