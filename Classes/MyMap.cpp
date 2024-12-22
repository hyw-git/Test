#include "MyMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

MyMap::MyMap() {
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;

    run_A = false;
    run_D = false;
    run_W = false;
    run_S = false;
    character.set_speed(40.0);
}

//������ʼ��ͼ����
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

//��ͼ��ʼ��
bool MyMap::init()
{
    if (!Scene::init())
        return false;
    const auto winSize = Director::getInstance()->getWinSize();    //��ȡ���ڳߴ�

    //�����ͼ
    mapTild = TMXTiledMap::create("map.tmx");
    mapTild->setAnchorPoint(Vec2(0.5, 0.5));
    mapTild->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(mapTild, 0);

    //�����ɫ����
    _sprite = Sprite::create("character.png");
    _sprite->setPosition(basic_size / 2 + winSize.width / 2, basic_size / 2 + winSize.height / 2);
    addChild(_sprite, 1);

    CalcSite();           //���»�ȡsprite��ǰλ����Ϣ

    //��꽻���İ�ť����
    auto set = MenuItemImage::create("exitSettingsNormal.png", "exitSettingsSelected.png", CC_CALLBACK_1(MyMap::Set, this));
    auto hoe = MenuItemImage::create("hoe.png", "hoe.png", CC_CALLBACK_1(MyMap::Change_Hoe, this));
    auto seed = MenuItemImage::create("seed.png", "seed.png", CC_CALLBACK_1(MyMap::Change_Seed, this));
    auto sickle = MenuItemImage::create("sickle.png", "sickle.png", CC_CALLBACK_1(MyMap::Change_Sickle, this));

    //�˵�λ������
    set->setPosition(900, 600);
    hoe->setAnchorPoint(Vec2(0.5, 0.5));
    hoe->setPosition(winSize.width / 2 - 3.5 * basic_size, basic_size / 2);
    seed->setAnchorPoint(Vec2(0.5, 0.5));
    seed->setPosition(winSize.width / 2 - 1.5 * basic_size, basic_size / 2);
    sickle->setAnchorPoint(Vec2(0.5, 0.5));
    sickle->setPosition(winSize.width / 2 - 2.5 * basic_size, basic_size / 2);

    auto menu = Menu::create(set, hoe, seed, sickle, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 4);

    auto goods = Sprite::create("goods.png");
    goods->setAnchorPoint(Vec2(0.5, 0.5));
    goods->setPosition(winSize.width / 2, basic_size / 2);
    this->addChild(goods, 3);

    //��������
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MyMap::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MyMap::onKeyReleased, this);

    //���¼���������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //���ڸ��£�������
    schedule([this](float deltaTime) {
        this->update(deltaTime);
        }, "update_key_listener_key");

    return true;
}

//���µ�ǰ������maptild�е�λ��
void MyMap::CalcSite() {
    spriteCurPos = ccp((int)(_sprite->getPositionX() - mapTild->getPositionX()) / basic_size + 24,
        ((int)(mapTild->getPositionY() - _sprite->getPositionY() + basic_size / 2)) / basic_size + 25);
}

//�ж�ÿһ֡���ƶ�
void MyMap::update(float deltaTime) {
    Node::update(deltaTime);
    spriteNextPos = spriteCurPos;
    TMXLayer* ly = mapTild->getLayer("layer1");

    if (moveLeft) {
        spriteNextPos.x -= 1;
        if (spriteNextPos.x < 0 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_A == false) {
            run_A = true;
            Ani_A();
        }
        if ((_sprite->getPositionX() < basic_size * 4) && (mapTild->getContentSize().width / 2 - mapTild->getPositionX()) > 30)
            mapTild->setPosition(mapTild->getPositionX() + character.get_speed() * deltaTime, mapTild->getPositionY());
        else if (_sprite->getPositionX() > 30) {

            _sprite->setPosition(_sprite->getPositionX() - character.get_speed() * deltaTime, _sprite->getPositionY());
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
            mapTild->setPosition(mapTild->getPositionX() - character.get_speed() * deltaTime, mapTild->getPositionY());
        else if (_sprite->getPositionX() < basic_size * 31)
            _sprite->setPosition(_sprite->getPositionX() + character.get_speed() * deltaTime, _sprite->getPositionY());
    }

    if (moveUp) {
        spriteNextPos.y -= 1;
        if (spriteNextPos.y < 0 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_W == false) {
            run_W = true;
            Ani_W();
        }
        if ((_sprite->getPositionY() > 320 + basic_size / 2 * 15) && (mapTild->getContentSize().height / 2 + mapTild->getPositionY()) > 670)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() - character.get_speed() * deltaTime);
        else if (!ly->getTileGIDAt(spriteNextPos) && _sprite->getPositionY() < basic_size * 21)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() + character.get_speed() * deltaTime);
    }

    if (moveDown) {
        spriteNextPos.y += 1;
        if (spriteNextPos.y > mapTild->getMapSize().height - 1 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_S == false) {
            run_S = true;
            Ani_S();
        }
        if ((_sprite->getPositionY() < basic_size * 4) && (mapTild->getContentSize().height / 2 - mapTild->getPositionY()) > 30)
            mapTild->setPosition(mapTild->getPositionX(), mapTild->getPositionY() + character.get_speed() * deltaTime);
        else if (_sprite->getPositionY() > 30)
            _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() - character.get_speed() * deltaTime);
    }
}

//���Ƶ�֡����
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

//���Ƶ�֡����
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

//���Ƶ�֡����
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

//���Ƶ�֡����
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

//���������¼��л�����Ӧ�����ͳ���
void MyMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    TMXLayer* ly;
    TMXLayer* ly1;
    switch (keyCode) {
    case K_ESC:
        Esc();
        break;
    case K_W:               //�����ƶ�
        moveUp = true;
        CalcSite();
        break;
    case K_S:               //�����ƶ�
        moveDown = true;
        CalcSite();
        break;
    case K_A:               //�����ƶ�
        moveLeft = true;
        CalcSite();
        break;
    case K_D:               //�����ƶ�
        moveRight = true;
        CalcSite();
        break;
    case K_B:               //�򿪱���
        Bag();
        break;
    case K_E:               //���뷿��
        Room();
        break;
    case K_F:               //�볡���ｻ��
        if (character.get_tool() == SEED) {
            ly = mapTild->getLayer("layer0");
            if (ly->getTileGIDAt(spriteCurPos, nullptr) == Ground) {
                ly = mapTild->getLayer("layer2");
                ly->setTileGID(SEED, spriteCurPos);
                character.Remove_Item(SEED, 1);
                cropX.push_back(spriteCurPos.x);
                cropY.push_back(spriteCurPos.y);
                scheduleOnce(schedule_selector(MyMap::onCropMature), 1.0);
            }
        }
        else if (character.get_tool() == HOE) {
            ly = mapTild->getLayer("layer0");
            ly1 = mapTild->getLayer("layer2");
            if (ly1->getTileGIDAt(spriteCurPos, nullptr) == STONE) {
                ly1->removeTileAt(spriteCurPos);
                character.Get_Item(STONE, 1);
            }
            else if (ly->getTileGIDAt(spriteCurPos, nullptr) == GRASS) {
                ly->setTileGID(Ground, spriteCurPos);
            }
        }
        else if (character.get_tool() == SICKLE) {
            ly = mapTild->getLayer("layer2");
            if (ly->getTileGIDAt(spriteCurPos, nullptr) == CROP) {
                ly->removeTileAt(spriteCurPos);
                character.Get_Item(CROP, 1);
                character.Get_Item(SEED, 2);
            }
        }
        break;
    case K_Q:
        ly = mapTild->getLayer("layer3");
        if (ly->getTileGIDAt(spriteCurPos, nullptr) == CHICKEN) {
            if (chicken.Can_Feeded_Again && character.Has_CROP(2)) {
                chicken.Feeded();
                character.Remove_Item(CROP, chicken.GetAppetite());
                scheduleOnce(schedule_selector(MyMap::Set_Feed_Status), 10.0);
                if (chicken.Get_Egg(1)) {
                    character.Get_Item(EGG, 1);
                }
            }
        }
        break;
    case K_L:
        ly = mapTild->getLayer("layer3");
        if (ly->getTileGIDAt(spriteCurPos, nullptr) == CHICKEN) {
            if (chicken.Killed()) {
                ly->removeTileAt(spriteCurPos);
                character.Get_Item(CHICKEN, 2);
            }
        }
    }
    return;
}

//�����Զ�����
void MyMap::onCropMature(float dt) {
    TMXLayer* ly = mapTild->getLayer("layer2");
    Vec2 Pos = ccp(*cropX.begin(), *cropY.begin());
    cropX.erase(cropX.begin());
    cropY.erase(cropY.begin());
    ly->setTileGID(CROP, Pos);
}

//������ι��ȴ
void MyMap::Set_Feed_Status(float dt) {
    chicken.Set_Feed_Status();
}

//��¼���̱��ɿ�
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
    CalcSite();
    return;
}

//esc����ͣ
void MyMap::Esc() {
    auto scene = Esc::createScene();
    Director::getInstance()->pushScene(scene);
}

//��������
void MyMap::Bag() {
    auto scene = Bag::createScene();
    Director::getInstance()->pushScene(scene);
}

//���뷿��
void MyMap::Room() {
    TMXLayer* ly = mapTild->getLayer("layer0");
    if (ly->getTileGIDAt(spriteCurPos, nullptr) == DOOR) {
        auto scene = Room::createMapScene();
        Director::getInstance()->pushScene(scene);
    }
}

//�ղ˵����������л�������
void MyMap::Set(Ref* obj) {
    auto scene = Esc::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMap::Change_Hoe(Ref* obj) {
    if (character.Has_Hoe())
        character.set_tool(HOE);
}

void MyMap::Change_Seed(Ref* obj) {
    if (character.Has_Seed())
        character.set_tool(SEED);
}

void MyMap::Change_Sickle(Ref* obj) {
    if (character.Has_Sickle())
        character.set_tool(SICKLE);
}

void MyMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}