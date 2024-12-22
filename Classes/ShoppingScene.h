#ifndef __SHOPPING_SCENE_H__
#define __SHOPPING_SCENE_H__

#include "cocos2d.h"
#include "Inventory.h"
#include <vector>

USING_NS_CC;

class ShoppingScene: public cocos2d::Scene
{
    int goodsTypeNum;
    std::vector<MenuItemToggle*> toggles;//大小应该初始化为 goodsTypeNum + 1
    int nowSelected;//记录目前被选中的商品选项
    static Inventory shopgoods;//商店库存
    static std::vector<int> prices;//存放所有商品各自的价格 vector的大小初始化 goodsTypeNum + 1

public:
    ShoppingScene();
    static cocos2d::Scene* createScene();
    //创建一个商品选项
    MenuItemToggle* createAToggle(
        SEL_MenuHandler selector, char* itemNormalName, char* itemSelectedName, char* itemDisabledName);
    //创建多个商品选项
    void createToggles();
    //toggle的回调函数
    void toggleIsPressed(Ref* obj);
    //确认按钮
    void confirmItem(Ref* pSender);
    virtual bool init();
    void closeShoppingScene(Ref* pSender);//关闭按钮
    void buyItem(Ref* pSender);//购买按钮

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(ShoppingScene);
};

#endif // __SHOPPING_SCENE_H__

