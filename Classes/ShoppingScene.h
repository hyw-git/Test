#ifndef __SHOPPING_SCENE_H__
#define __SHOPPING_SCENE_H__

#include "cocos2d.h"
#include "Inventory.h"
#include <vector>

USING_NS_CC;

class ShoppingScene: public cocos2d::Scene
{
    int goodsTypeNum;
    std::vector<MenuItemToggle*> toggles;//��СӦ�ó�ʼ��Ϊ goodsTypeNum + 1
    int nowSelected;//��¼Ŀǰ��ѡ�е���Ʒѡ��
    static Inventory shopgoods;//�̵���
    static std::vector<int> prices;//���������Ʒ���Եļ۸� vector�Ĵ�С��ʼ�� goodsTypeNum + 1

public:
    ShoppingScene();
    static cocos2d::Scene* createScene();
    //����һ����Ʒѡ��
    MenuItemToggle* createAToggle(
        SEL_MenuHandler selector, char* itemNormalName, char* itemSelectedName, char* itemDisabledName);
    //���������Ʒѡ��
    void createToggles();
    //toggle�Ļص�����
    void toggleIsPressed(Ref* obj);
    //ȷ�ϰ�ť
    void confirmItem(Ref* pSender);
    virtual bool init();
    void closeShoppingScene(Ref* pSender);//�رհ�ť
    void buyItem(Ref* pSender);//����ť

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(ShoppingScene);
};

#endif // __SHOPPING_SCENE_H__

