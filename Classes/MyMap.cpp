#include "MyMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define basic_size 30

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
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    
    //create TMX map
    mapTild = TMXTiledMap::create("map.tmx");
    mapTild->setAnchorPoint(Vec2(0.5, 0.5));
    mapTild->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(mapTild);
    
    //create sprite
    _sprite = Sprite::create("character.png");
    _sprite->setPosition(basic_size / 2 + winSize.width / 2, basic_size / 2  + winSize.height / 2);
    addChild(_sprite);

    //监听键盘
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MyMap::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MyMap::onKeyReleased, this);
    
    //可实现监听按住键盘不松事件（待修改）
#if 0
    this->scheduleUpdate();
    auto listener = EventListenerKeyboard::create();;
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keys[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keys[keyCode] = false;
    };

#endif

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// w a s d 被按下
void MyMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
//  keys[keyCode] = true;
    //sprite当前位置
    Point spriteCurPos = ccp((int)(_sprite->getPositionX() - mapTild->getPositionX()) / basic_size + 25,
        (mapTild->getPositionY() - _sprite->getPositionY()) / basic_size + 25);
    //sprite下一步位置
    Point spriteNextPos = spriteCurPos;
    TMXLayer* ly = mapTild->getLayer("layer1");       //获取图层信息

    int gid = 0;

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:   //上移
        spriteNextPos.y -= 1;
        if (spriteNextPos.y < 0) return;  //边界检测。以下同理
        gid = ly->getTileGIDAt(spriteNextPos);
        if (gid) return;                  //障碍物判断
        //通过边界和障碍物检测后，控制地图和人物移动
        if ((_sprite->getPositionY() == 320 + basic_size / 2 * 15) && (mapTild->getContentSize().height / 2 + mapTild->getPositionY()) > 670)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() - basic_size);
        else if (_sprite->getPositionY() < basic_size * 21)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() + basic_size);
        break;

    case EventKeyboard::KeyCode::KEY_S:   //下移
        spriteNextPos.y += 1;
        if (spriteNextPos.y > mapTild->getMapSize().height - 1) return;
        gid = ly->getTileGIDAt(spriteNextPos);
        if (gid) return;
        if ((_sprite->getPositionY() < basic_size * 4) && (mapTild->getContentSize().height / 2 - mapTild->getPositionY()) > 30)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() + basic_size);
        else if (_sprite->getPositionY() > 30)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() - basic_size);
        break;

    case EventKeyboard::KeyCode::KEY_A:  //左移
        spriteNextPos.x -= 1;
        if (spriteNextPos.x < 0) return;
        gid = ly->getTileGIDAt(spriteNextPos);
        if (gid) return;
        if ((_sprite->getPositionX() < basic_size * 4) && (mapTild->getContentSize().width / 2 - mapTild->getPositionX()) > 30)
            mapTild->setPosition(mapTild->getPositionX() + basic_size, mapTild->getPositionY());
        else if (_sprite->getPositionX() > 30)
            _sprite->setPosition(_sprite->getPositionX() - basic_size, _sprite->getPositionY());
        break;

    case EventKeyboard::KeyCode::KEY_D:  //右移
        spriteNextPos.x += 1;
        if (spriteNextPos.x > mapTild->getMapSize().width - 1) return;
        gid = ly->getTileGIDAt(spriteNextPos);
        if (gid) return;
        if ((_sprite->getPositionX() == 480 + basic_size / 2 * 23) && (mapTild->getContentSize().width / 2 + mapTild->getPositionX()) > 960)
            mapTild->setPosition(mapTild->getPositionX() - basic_size, mapTild->getPositionY());
        else if (_sprite->getPositionX() < basic_size * 31)
            _sprite->setPosition(_sprite->getPositionX() + basic_size, _sprite->getPositionY());
        break;
}
    return;
}

//记录键盘被松开
void MyMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    keys[keyCode] = false;
}

//键盘按住事件相关函数
#if 0
void MyMap::resetTimer() {
    frameIndex = 0;
    nextKeyFrameIndex = rand() % 120 + 60 * 60;
}

void MyMap::update(float dt) {
    frameIndex++;
    if (frameIndex >= nextKeyFrameIndex) {
        if (isKeyPressed(EventKeyboard::KeyCode::KEY_W))
            keyPressedDuration(EventKeyboard::KeyCode::KEY_W);
        else if (isKeyPressed(EventKeyboard::KeyCode::KEY_S))
            keyPressedDuration(EventKeyboard::KeyCode::KEY_S);
        else if (isKeyPressed(EventKeyboard::KeyCode::KEY_A))
            keyPressedDuration(EventKeyboard::KeyCode::KEY_A);
        else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D))
            keyPressedDuration(EventKeyboard::KeyCode::KEY_D);
    }
/*  if (isKeyPressed(EventKeyboard::KeyCode::KEY_W))
        keyPressedDuration(EventKeyboard::KeyCode::KEY_W);
    else if (isKeyPressed(EventKeyboard::KeyCode::KEY_S))
        keyPressedDuration(EventKeyboard::KeyCode::KEY_S);
    else if (isKeyPressed(EventKeyboard::KeyCode::KEY_A))
        keyPressedDuration(EventKeyboard::KeyCode::KEY_A);
    else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D))
        keyPressedDuration(EventKeyboard::KeyCode::KEY_D);*/
}

bool MyMap::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if (keys[keyCode])
        return true;
    else
        return false;
}
#endif


#if 0
void MyMap::keyPressedDuration(EventKeyboard::KeyCode keyCode) {
    int offsetX = 0, offsetY = 0;
    int M_offsetX = 0, M_offsetY = 0;
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        if ((_sprite->getPositionY() > basic_size * 15) && (mapTild->getContentSize().height / 2 + mapTild->getPositionY()) > 600)
            M_offsetY = 0 - basic_size;
        else if (_sprite->getPositionY() < basic_size * 18)
            offsetY = basic_size;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        offsetY = 0 - basic_size;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        offsetX = 0 - basic_size;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        offsetX = basic_size;
        break;
    }
    auto moveTo = MoveTo::create(1, Vec2(_sprite->getPositionX() + offsetX, _sprite->getPositionY() + offsetY));
    auto M_moveTo = MoveTo::create(1, Vec2(mapTild->getPositionX() + M_offsetX, mapTild->getPositionY() + M_offsetY));
    _sprite->runAction(moveTo);
    mapTild->runAction(M_moveTo);
    return;
}
#endif

void MyMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}