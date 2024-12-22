#include "EscScene.h"
#include "Def.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
USING_NS_CC;

//创建一个登录场景
Scene* Esc::createScene()
{
    auto scene = Scene::create();
    auto layer = Esc::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//登陆界面初始化
bool Esc::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spriteBack = Sprite::create("suspendscene.jpg");

    /************************
     * 设置背景图精灵位置信息
     * 锚点：    （0.5, 0.5）
     * 位置：     窗口中心
     * 竖直放缩： 1.2倍
    ************************/
    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spriteBack->setScale(1.5);
    this->addChild(spriteBack);

    //设置菜单（start/end）
    auto menuStart = MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(Esc::continueGame, this));
    menuStart->setScale(1.5);
    menuStart->setPosition(visibleSize.width / 2 + origin.x - 100, 200);

    auto menuEnd = MenuItemImage::create("quit.png", "quit.png", CC_CALLBACK_1(Esc::endGame, this));
    menuEnd->setScale(1.5);
    menuEnd->setPosition(visibleSize.width / 2 + origin.x + 100, 200);

    auto settingsItem = MenuItemImage::create("SettingsNormal.png", "SettingsSelected.png", CC_CALLBACK_1(Esc::enterSettings, this));
    settingsItem->setScale(1.5);
    settingsItem->setPosition(settingsItem->getContentSize().width, settingsItem->getContentSize().height);

    auto menu = Menu::create(menuStart, menuEnd, settingsItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void Esc::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//start game
void Esc::continueGame(Ref* obj) { 
    Director::getInstance()->popScene();
}

//end game
void Esc::endGame(Ref* obj) {
    Director::getInstance()->end();
}

void Esc::enterSettings(Ref* obj)
{
    auto setscene = Settings::createSettingsScene();
    Director::getInstance()->pushScene(TransitionMoveInB::create(0.5, setscene));
}