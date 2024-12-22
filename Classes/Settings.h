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
	static cocos2d::Scene* createSettingsScene(); //����"����"����
    virtual bool init();                          //"����"������ʼ��

    void exitSettings(Ref* obj);                  //"�˳�����"�İ�ť
    void volumeTurnOn();                          //��������
    void volumeTurnOff();                         //�����ر�
    void volumeOnOffCallback(Ref* obj);           //�л��˵���
    void archiveGame(Ref* obj);

    void shopItem(Ref* obj);////�̵갴ť/*****///��ʱ��������

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Settings);
};
#endif // __SETTINGS_H__
