#include "MyMap.h"
#include "GameBeginScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
#define basic_size 30

#define Ground 2929
#define SEED 4225
#define CROP 4224

#define K_W  EventKeyboard::KeyCode::KEY_W
#define K_S  EventKeyboard::KeyCode::KEY_S
#define K_A  EventKeyboard::KeyCode::KEY_A
#define K_D  EventKeyboard::KeyCode::KEY_D
#define K_F  EventKeyboard::KeyCode::KEY_F
#define K_C  EventKeyboard::KeyCode::KEY_C
#define K_ESC EventKeyboard::KeyCode::KEY_ESCAPE

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
    const auto winSize = Director::getInstance()->getWinSize();    //获取窗口尺寸
    
    //Add TMX map
    mapTild = TMXTiledMap::create("map.tmx");
    mapTild->setAnchorPoint(Vec2(0.5, 0.5));
    mapTild->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(mapTild);
    
    //Add sprite
    _sprite = Sprite::create("character.png");
    _sprite->setPosition(basic_size / 2 + winSize.width / 2, basic_size / 2  + winSize.height / 2);
    addChild(_sprite);

    //更新获取sprite当前位置信息
    CalcSite();                    

    auto set = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MyMap::Set, this));
    set->setPosition(900, 600);
     
    auto menu = Menu::create(set, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //监听键盘
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MyMap::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MyMap::onKeyReleased, this);

    //将事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //定期更新，处理长按
    schedule([this](float deltaTime) {
        this->update(deltaTime);
        }, "update_key_listener_key");

    return true;
}

//更新当前主角在maptild中的位置
void MyMap::CalcSite() {
    spriteCurPos = ccp((int)(_sprite->getPositionX() - mapTild->getPositionX()) / basic_size + 25,
                       ((int)(mapTild->getPositionY() - _sprite->getPositionY() + basic_size / 2)) / basic_size + 24);
}

//判断每一帧的移动
void MyMap::update(float deltaTime) {
    Node::update(deltaTime);
    Point spriteNextPos = spriteCurPos;
    TMXLayer* ly = mapTild->getLayer("layer1");

    if (moveLeft) {
        spriteNextPos.x -= 1;
        if (spriteNextPos.x < 0 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_A == false) {
            run_A = true;
            Ani_A();
        }
        if ((_sprite->getPositionX() < basic_size * 4) && (mapTild->getContentSize().width / 2 - mapTild->getPositionX()) > 30)
            mapTild->setPosition(mapTild->getPositionX() + moveSpeed * deltaTime, mapTild->getPositionY());
        else if (_sprite->getPositionX() > 30) {
            
            _sprite->setPosition(_sprite->getPositionX() - moveSpeed * deltaTime, _sprite->getPositionY());
        }
    }

    if (moveRight) {
        spriteNextPos.x += 1;
        if (spriteNextPos.x > mapTild->getMapSize().width - 1 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_D == false) {
            run_D = true;
            Ani_D();
        }
        if ((_sprite->getPositionX() > 480 + basic_size / 2 * 23) && (mapTild->getContentSize().width / 2 + mapTild->getPositionX()) > 960)
            mapTild->setPosition(mapTild->getPositionX() - moveSpeed * deltaTime, mapTild->getPositionY());
        else if (_sprite->getPositionX() < basic_size * 31)
            _sprite->setPosition(_sprite->getPositionX() + moveSpeed * deltaTime, _sprite->getPositionY());
    }

    if (moveUp) {
        spriteNextPos.y -= 1;
        if (spriteNextPos.y < 0 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_W == false) {
            run_W = true;
            Ani_W();
        }
        if ((_sprite->getPositionY() > 320 + basic_size / 2 * 15) && (mapTild->getContentSize().height / 2 + mapTild->getPositionY()) > 670)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() - moveSpeed * deltaTime);
        else if (!ly->getTileGIDAt(spriteNextPos) && _sprite->getPositionY() < basic_size * 21)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() + moveSpeed * deltaTime);
    }

    if (moveDown) {
        spriteNextPos.y += 1;
        if (spriteNextPos.y > mapTild->getMapSize().height - 1 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_S == false) {
            run_S = true;
            Ani_S();
        }
        if ((_sprite->getPositionY() < basic_size * 4) && (mapTild->getContentSize().height / 2 - mapTild->getPositionY()) > 30)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() + moveSpeed * deltaTime);
        else if (_sprite->getPositionY() > 30)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() - moveSpeed * deltaTime);
    }
}

//左移的帧动画
void MyMap::Ani_A() {
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 0; i < 3; i++) {
        char imageName[20];
        sprintf(imageName, "Run_A_%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(imageName, Rect(0, 0, 30, 30));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.2);
    ani->setLoops(-1);
    Animate* animate = Animate::create(ani);
    _sprite->runAction(animate);
}

//右移的帧动画
void MyMap::Ani_D() {
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 0; i < 3; i++) {
        char imageName[20];
        sprintf(imageName, "Run_D_%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(imageName, Rect(0, 0, 30, 30));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.2);
    ani->setLoops(-1);
    Animate* animate = Animate::create(ani);
    _sprite->runAction(animate);
}

//上移的帧动画
void MyMap::Ani_W() {
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 0; i < 3; i++) {
        char imageName[20];
        sprintf(imageName, "Run_W_%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(imageName, Rect(0, 0, 30, 30));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.2);
    ani->setLoops(-1);
    Animate* animate = Animate::create(ani);
    _sprite->runAction(animate);
}

//下移的帧动画
void MyMap::Ani_S() {
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 0; i < 3; i++) {
        char imageName[20];
        sprintf(imageName, "Run_S_%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(imageName, Rect(0, 0, 30, 30));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.2);
    ani->setLoops(-1);
    Animate* animate = Animate::create(ani);
    _sprite->runAction(animate);
}

//监听键盘事件切换到对应函数和场景
void MyMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case K_ESC:
        Esc();
        break;
    case K_W:               //向上移动
        moveUp = true;
        CalcSite();
        break;
    case K_S:               //向下移动
        moveDown = true;
        CalcSite();
        break;
    case K_A:               //向左移动
        moveLeft = true;
        CalcSite();
        break;
    case K_D:               //向右移动
        moveRight = true;   
        CalcSite();
        break;
    case K_F:               //与场景物交互
        TMXLayer* ly = mapTild->getLayer("layer0");
        if (ly->getTileGIDAt(spriteCurPos, nullptr) == Ground) {
            ly = mapTild->getLayer("layer2");
            ly->setTileGID(SEED, spriteCurPos);
            cropX.push_back(spriteCurPos.x);
            cropY.push_back(spriteCurPos.y);
            scheduleOnce(schedule_selector(MyMap::onCropMature), 2.0);
        }
//       else if (ly->getTileGIDAt(spriteCurPos, nullptr) == ) {}
        break;
    }

    return;
}

//作物自动生长
void MyMap::onCropMature(float dt) {
    TMXLayer* ly = mapTild->getLayer("layer2");
    Vec2 Pos = ccp(*cropX.begin(), *cropY.begin());
    cropX.erase(cropX.begin());
    cropY.erase(cropY.begin());
    ly->setTileGID(CROP, Pos);
}

//记录键盘被松开
void MyMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == K_W) {
        moveUp = run_W = false;
        _sprite->stopAllActions();
    }
    else if (keyCode == K_S) {
        moveDown = run_S = false;
        _sprite->stopAllActions();
    }
    else if (keyCode == K_A) {
        moveLeft = run_A = false;
        _sprite->stopAllActions();
    }
    else if (keyCode == K_D) {
        moveRight = run_D = false;
        _sprite->stopAllActions();
    }
    return;
}

//esc键暂停
void MyMap::Esc() {
    auto scene = Esc::createScene();
    Director::getInstance()->pushScene(scene);
}

//空菜单（可用于切换场景）
void MyMap::Set(Ref* obj) {

}

void MyMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}