#include "GamebeginScene.h"
#include "MyMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//创建一个登录场景
Scene* GameBegin::createScene()
{
    auto scene = Scene::create();
    auto layer = GameBegin::create();
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
bool GameBegin::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    //background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spriteBack = Sprite::create("Begin.png");

    /************************
     * 设置背景图精灵位置信息
     * 锚点：    （0.5, 0.5）
     * 位置：     窗口中心
     * 竖直放缩： 1.2倍
    ************************/
    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spriteBack->setScaleY(1.2);
    this->addChild(spriteBack); 

    //设置菜单（start/end）   *图标资源暂时借用，当作占位符*
    auto menuStart = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameBegin::startGame, this));
    menuStart->setPosition(visibleSize.width / 2 + origin.x, 200);

    auto menuEnd = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameBegin::endGame, this));
    menuEnd->setPosition(visibleSize.width / 2 + origin.x, 100);

    auto menu = Menu::create(menuStart, menuEnd, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//start game
void GameBegin::startGame(Ref* obj) {         //切换场景
    auto scene = MyMap::createMapScene();
    Director::getInstance()->replaceScene
    (TransitionCrossFade::create(1, scene));
}

//end game
void GameBegin::endGame(Ref* obj) {
    Director::getInstance()->end();
}
