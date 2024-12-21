#include "EscScene.h"
#include "Def.h"
#include "SimpleAudioEngine.h"

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

    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spriteBack->setScale(1.5);
    this->addChild(spriteBack);

    //设置菜单（continue/end）
    auto menuStart = MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(Esc::continueGame, this));
    menuStart->setScale(1.5);
    menuStart->setPosition(visibleSize.width / 2 + origin.x - 100, 200);

    auto menuEnd = MenuItemImage::create("quit.png", "quit.png", CC_CALLBACK_1(Esc::endGame, this));
    menuEnd->setScale(1.5);
    menuEnd->setPosition(visibleSize.width / 2 + origin.x + 100, 200);

    auto menu = Menu::create(menuStart, menuEnd, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void Esc::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//继续游戏
void Esc::continueGame(Ref* obj) { 
    Director::getInstance()->popScene();
}

//结束游戏
void Esc::endGame(Ref* obj) {
    Director::getInstance()->end();
}