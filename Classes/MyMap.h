#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include "cocos2d.h"
#include "EscScene.h"
#include<vector>
USING_NS_CC;

class MyMap : public cocos2d::Scene
{
    friend class CropGrowthTimer;
private:
    TMXTiledMap* mapTild;      //��Ƭ��ͼ
    Sprite* _sprite;           //���Ǿ���
    Point spriteCurPos;        //���ǵ�ǰ�ڵ�ͼ�е�λ��
    std::vector<float> cropX;
    std::vector<float> cropY;

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool run_A = false;
    bool run_D = false;
    bool run_W = false;
    bool run_S = false;

    float moveSpeed = 40.0f;

public:
    static cocos2d::Scene* createMapScene();    //������ͼ����
    virtual bool init();                        //������ʼ��

    void update(float deltaTime);

    //�������º��ɿ�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void CalcSite();                              //��������sprite��ǰλ��
    void Move(EventKeyboard::KeyCode keyCode);    //��������sprite�ƶ�(WASD)
    void Ani_A();  //����֡����
    void Ani_D();  //����֡����
    void Ani_W();  //����֡����
    void Ani_S();  //����֡����

    //���ð�ť
    void Set(Ref* obj);  //���ղ˵���ť��
    void Esc();    //esc���˳�

    void onCropMature(float dt);  //��������

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
