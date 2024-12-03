#include "MyMap.h"
#include "GameBeginScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
#define basic_size 30
#define Ground 948
#define K_W  EventKeyboard::KeyCode::KEY_W
#define K_S  EventKeyboard::KeyCode::KEY_S
#define K_A  EventKeyboard::KeyCode::KEY_A
#define K_D  EventKeyboard::KeyCode::KEY_D
#define K_F  EventKeyboard::KeyCode::KEY_F
#define K_C  EventKeyboard::KeyCode::KEY_C


//创建初始地图场景
Scene* MyMap::createMapScene()
{
    auto scene = Scene::create();
    auto layer = MyMap::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//地图初始化
bool MyMap::init()
{
    if (!Scene::init())
        return false;
    auto winSize = Director::getInstance()->getWinSize();    //获取窗口尺寸
    
    //Add TMX map
    mapTild = TMXTiledMap::create("map.tmx");
    mapTild->setAnchorPoint(Vec2(0.5, 0.5));
    mapTild->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(mapTild);
    
    //Add sprite
    _sprite = Sprite::create("character.png");
    _sprite->setPosition(basic_size / 2 + winSize.width / 2, basic_size / 2  + winSize.height / 2);
    addChild(_sprite);
    CalcSite();                    //更新获取sprite当前位置信息


    //监听键盘
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MyMap::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MyMap::onKeyReleased, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

//更新当前主角在maptild中的位置
void MyMap::CalcSite() {
    spriteCurPos = ccp((int)(_sprite->getPositionX() - mapTild->getPositionX()) / basic_size + 25,
        (mapTild->getPositionY() - _sprite->getPositionY() - basic_size / 2) / basic_size + 25);
}

//控制主角和地图的移动逻辑
void MyMap::Move(EventKeyboard::KeyCode keyCode) {
    Point spriteNextPos = spriteCurPos;
    TMXLayer* ly = mapTild->getLayer("layer1");
    switch (keyCode) {
        case K_W:
            spriteNextPos.y -= 1;
            if (spriteNextPos.y < 0 || ly->getTileGIDAt(spriteNextPos)) return;
            if ((_sprite->getPositionY() == 320 + basic_size / 2 * 15) && (mapTild->getContentSize().height / 2 + mapTild->getPositionY()) > 670)
                mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() - basic_size);
            else if (_sprite->getPositionY() < basic_size * 21)
                _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() + basic_size);
            break;
        case K_S:
            spriteNextPos.y += 1;
            if (spriteNextPos.y > mapTild->getMapSize().height - 1 || ly->getTileGIDAt(spriteNextPos)) return;
            if ((_sprite->getPositionY() < basic_size * 4) && (mapTild->getContentSize().height / 2 - mapTild->getPositionY()) > 30)
                mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() + basic_size);
            else if (_sprite->getPositionY() > 30)
                _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() - basic_size);
            break;
        case K_A:
            spriteNextPos.x -= 1;
            if (spriteNextPos.x < 0 || ly->getTileGIDAt(spriteNextPos)) return;
            if ((_sprite->getPositionX() < basic_size * 4) && (mapTild->getContentSize().width / 2 - mapTild->getPositionX()) > 30)
                mapTild->setPosition(mapTild->getPositionX() + basic_size, mapTild->getPositionY());
            else if (_sprite->getPositionX() > 30)
                _sprite->setPosition(_sprite->getPositionX() - basic_size, _sprite->getPositionY());
            break;
        case K_D:
            spriteNextPos.x += 1;
            if (spriteNextPos.x > mapTild->getMapSize().width - 1 || ly->getTileGIDAt(spriteNextPos)) return;
            if ((_sprite->getPositionX() == 480 + basic_size / 2 * 23) && (mapTild->getContentSize().width / 2 + mapTild->getPositionX()) > 960)
                mapTild->setPosition(mapTild->getPositionX() - basic_size, mapTild->getPositionY());
            else if (_sprite->getPositionX() < basic_size * 31)
                _sprite->setPosition(_sprite->getPositionX() + basic_size, _sprite->getPositionY());
            break;
    }
    return;
}

//监听键盘事件切换到对应函数和场景
void MyMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
        case K_W:               //向上移动
        case K_S:               //向下移动
        case K_A:               //向左移动
        case K_D:               //向右移动
            Move(keyCode);
            CalcSite();
            break;
        case K_F:               //与场景物交互
            TMXLayer* ly = mapTild->getLayer("layer0");
            if (ly->getTileGIDAt(spriteCurPos, nullptr) == Ground)
                ly->setTileGID(960, spriteCurPos);
            break;
#if 0
        case K_C:               //快捷键、换场景
            auto scene = ;
            Director::getInstance()->pushScene(scene);
#endif
    }
    return;
}

//记录键盘被松开
void MyMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    return;
}

void MyMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}