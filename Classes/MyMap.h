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
    TMXTiledMap* mapTild;      //瓦片地图
    Sprite* _sprite;           //主角精灵
    Point spriteCurPos;        //主角当前在地图中的位置
    Point spriteNextPos;

    //记录庄稼坐标
    std::vector<float> cropX;
    std::vector<float> cropY;

    //移动键记录
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;

    //跑动动画记录
    bool run_A;
    bool run_D;
    bool run_W;
    bool run_S;

public:
    MyMap();                                    //默认构造函数
    static cocos2d::Scene* createMapScene();    //创建地图场景
    virtual bool init();                        //场景初始化

    void update(float deltaTime);               //帧检测移动

    //监听按下和松开键盘
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void CalcSite();                              //计算主角sprite当前位置

    //设置按钮
    void Set(Ref* obj);  //（空菜单按钮）
    void Change_Hoe(Ref* obj);
    void Change_Seed(Ref* obj);
    void Change_Sickle(Ref* obj);
    void Esc();    //esc键退出
    void Bag();
    void Room();

    void onCropMature(float dt);  //作物生长
    void Ani_A();  //左移帧动画
    void Ani_D();  //右移帧动画
    void Ani_W();  //上移帧动画
    void Ani_S();  //下移帧动画

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
