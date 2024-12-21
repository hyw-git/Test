#include "RoomScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Room::Room() {
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;

    run_A = false;
    run_D = false;
    run_W = false;
    run_S = false;
    speed = 40.0f;
}

//������ʼ��ͼ����
Scene* Room::createMapScene()
{
    auto scene = Scene::create();
    auto layer = Room::create();
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
bool Room::init()
{
    if (!Scene::init())
        return false;
    const auto winSize = Director::getInstance()->getWinSize();    //��ȡ���ڳߴ�

    //Add TMX map
    mapTild = TMXTiledMap::create("room.tmx");
    mapTild->setAnchorPoint(Vec2(0.5, 0.5));
    mapTild->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(mapTild, 0);

    //Add sprite
    _sprite = Sprite::create("character.png");
    _sprite->setPosition(winSize.width / 2 + 5 * basic_size, winSize.height / 2 - 7 * basic_size);
    addChild(_sprite, 1);

    //���»�ȡsprite��ǰλ����Ϣ
    CalcSite();

    //��������
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Room::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Room::onKeyReleased, this);

    //���¼���������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //���ڸ��£�������
    schedule([this](float deltaTime) {
        this->update(deltaTime);
        }, "update_key_listener_key");

    return true;
}

//���µ�ǰ������maptild�е�λ��
void Room::CalcSite() {
    spriteCurPos = ccp((int)(_sprite->getPositionX() - mapTild->getPositionX()) / basic_size + 7,
        ((int)(mapTild->getPositionY() - _sprite->getPositionY() + basic_size / 2)) / basic_size + 7);
}

//�ж�ÿһ֡���ƶ�
void Room::update(float deltaTime) {
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
        _sprite->setPosition(_sprite->getPositionX() - speed * deltaTime, _sprite->getPositionY());
    }

    if (moveRight) {
        spriteNextPos.x += 1;
        if (spriteNextPos.x > mapTild->getMapSize().width - 1 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_D == false) {
            run_D = true;
            Ani_D();
        }
        _sprite->setPosition(_sprite->getPositionX() + speed * deltaTime, _sprite->getPositionY());
    }

    if (moveUp) {
        spriteNextPos.y -= 1;
        if (spriteNextPos.y < 0 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_W == false) {
            run_W = true;
            Ani_W();
        }
         _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() + speed * deltaTime);
    }

    if (moveDown) {
        spriteNextPos.y += 1;
        if (spriteNextPos.y > mapTild->getMapSize().height - 1 || ly->getTileGIDAt(spriteNextPos)) return;
        if (run_S == false) {
            run_S = true;
            Ani_S();
        } 
        _sprite->setPosition(_sprite->getPositionX(), _sprite->getPositionY() - speed * deltaTime);
    }
}

//���Ƶ�֡����
void Room::Ani_A() {
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
void Room::Ani_D() {
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
void Room::Ani_W() {
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
void Room::Ani_S() {
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
void Room::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    TMXLayer* ly;
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
    case K_E:               //������
        ly = mapTild->getLayer("layer0");
        if (ly->getTileGIDAt(spriteCurPos, nullptr) == ROOM_DOOR)
            Director::getInstance()->popScene();
        break;
    case K_B:               //�򿪱���
        bag();
        break;
    case K_F:               //�ϳ�
        ly = mapTild->getLayer("layer0");
        if (ly->getTileGIDAt(spriteCurPos, nullptr) == COM) {
            character.Remove_Item(STONE, 2);
            character.Get_Item(SICKLE, 1);
            auto myLabel = Label::createWithSystemFont("+ SICKLE * 1", "Arial", 16);
            myLabel->setPosition(Vec2(80, 20));
            myLabel->setVisible(true);
            this->addChild(myLabel);
        }
    }
    return;
}

//��¼���̱��ɿ�
void Room::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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
void Room::Esc() {
    auto scene = Esc::createScene();
    Director::getInstance()->pushScene(scene);
}

//�򿪱���
void Room::bag() {
    auto scene = Bag::createScene();
    Director::getInstance()->pushScene(scene);
}

void Room::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}