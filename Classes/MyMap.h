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
    TMXTiledMap* mapTild;      //瓦片地图
    Sprite* _sprite;           //主角精灵
    Point spriteCurPos;        //主角当前在地图中的位置
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
    static cocos2d::Scene* createMapScene();    //创建地图场景
    virtual bool init();                        //场景初始化

    void update(float deltaTime);

    //监听按下和松开键盘
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void CalcSite();                              //计算主角sprite当前位置
    void Move(EventKeyboard::KeyCode keyCode);    //控制主角sprite移动(WASD)
    void Ani_A();  //左移帧动画
    void Ani_D();  //右移帧动画
    void Ani_W();  //上移帧动画
    void Ani_S();  //下移帧动画

    //设置按钮
    void Set(Ref* obj);  //（空菜单按钮）
    void Esc();    //esc键退出

    void onCropMature(float dt);  //作物生长

    void menuCloseCallback(cocos2d::Ref* pSender);// a selector callback
    CREATE_FUNC(MyMap);                           // implement the "static create()" method manually
};
#endif
