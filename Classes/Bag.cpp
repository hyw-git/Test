#include "Bag.h"
//#include "SimpleAudioEngine.h"

USING_NS_CC;

Bag::Bag() {
    character = Character::getInstance();
}

//创建一个登录场景
Scene* Bag::createScene()
{
    auto scene = Scene::create();
    auto layer = Bag::create();
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
bool Bag::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spriteBack = Sprite::create("bag.png");
    auto background = Sprite::create("Begin.png");

    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background);

    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(spriteBack);

    auto menuEnd = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(Bag::close, this));
    menuEnd->setPosition(visibleSize.width / 2 + 320, 495);

    auto menu = Menu::create(menuEnd, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void Bag::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//start game
void Bag::close(Ref* obj) {         //切换场景
    Director::getInstance()->popScene();
}
