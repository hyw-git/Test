#include "GamebeginScene.h"
#include "MyMap.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"

USING_NS_CC;

//����һ����¼����
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

//��½�����ʼ��
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
     * ���ñ���ͼ����λ����Ϣ
     * ê�㣺    ��0.5, 0.5��
     * λ�ã�     ��������
     * ��ֱ������ 1.2��
    ************************/
    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spriteBack->setScaleY(1.2);
    this->addChild(spriteBack); 

    //���ò˵���start/end��
    auto menuStart = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(GameBegin::startGame, this));
    menuStart->setScale(1.5);
    menuStart->setPosition(visibleSize.width / 2 + origin.x - 100, 200);

    auto menuEnd = MenuItemImage::create("quit.png", "quit.png", CC_CALLBACK_1(GameBegin::endGame, this));
    menuEnd->setScale(1.5);
    menuEnd->setPosition(visibleSize.width / 2 + origin.x + 100, 200);

    auto settingsItem = MenuItemImage::create("SettingsNormal.png", "SettingsSelected.png", CC_CALLBACK_1(GameBegin::enterSettings, this));
    settingsItem->setScale(1.5);
    settingsItem->setPosition(settingsItem->getContentSize().width, settingsItem->getContentSize().height);

    /*auto ReadFileItem = MenuItemImage::create("ReadFileNormal.png", "ReadFileSelected.png", CC_CALLBACK_1(GameBegin::readFileToStartGame, this));
    ReadFileItem->setScale(1.5);
    ReadFileItem->setPosition(visibleSize.width / 2 + origin.x - 200, 200);*/

    auto menu = Menu::create(menuStart, menuEnd, settingsItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//start game
void GameBegin::startGame(Ref* obj) {         //�л�����
    auto scene = MyMap::createMapScene();
    Director::getInstance()->replaceScene
    (TransitionCrossFade::create(1, scene));
}

//end game
void GameBegin::endGame(Ref* obj) {
    Director::getInstance()->end();
}

void GameBegin::enterSettings(Ref* obj)
{
    auto setscene = Settings::createSettingsScene();
    Director::getInstance()->pushScene(TransitionMoveInB::create(0.5, setscene));
}

void GameBegin::readFileToStartGame(Ref* obj)
{
#define READ_FILE
    auto scene = MyMap::createMapScene();
    Director::getInstance()->replaceScene
    (TransitionCrossFade::create(1, scene));
}
