#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
//#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class Settings :public cocos2d::Scene
{
    MenuItemImage* volumeOffItem;
    MenuItemImage* volumeOnItem;
    ui::Slider* volumeSlider;
    SimpleAudioEngine* audio;
    MenuItemToggle* archiveItemToggle;

public:
	static cocos2d::Scene* createSettingsScene(); //创建"设置"场景
    virtual bool init();                          //"设置"场景初始化

    void exitSettings(Ref* obj);                  //"退出设置"的按钮
    void volumeTurnOn();                          //音量开启
    void volumeTurnOff();                         //音量关闭
    void volumeOnOffCallback(Ref* obj);           //切换菜单项
    void archiveGame(Ref* obj);

    void shopItem(Ref* obj);////商店按钮/*****///暂时用作测试

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Settings);
};
#endif // __SETTINGS_H__
