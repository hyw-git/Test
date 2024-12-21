#include "Bag.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using std::to_string;

//创建一个背包场景
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
        return false;

    //背包背景图片设置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spriteBack = Sprite::create("bag.png");               //背包框架图片
    auto background = Sprite::create("Begin.png");             //场景背景图片

    //设置图片位置
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background);

    //设置图片位置
    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(spriteBack);

    //获取背包信息
    int id, cus, num;                         //物品id，数量，背包容量
    int init_x = 220, init_y = 470;           //初始图片基点位置
    int init_x_num = 250, init_y_num = 445;   //初始数字基点位置
    cus = character.Get_cus();                //获取背包已有容量
    if (cus != -1) {
        for (int ix = 0; ix < cus; ix++, init_x += 75, init_x_num += 75) {
            character.Get_Message(ix, id, num);           //获取每一格中的物品信息
            if (id == HOE) {                              //锄头的有关显示信息
                auto item = Sprite::create("hoe.png");
                item->setAnchorPoint(Vec2(0.5, 0.5));
                item->setScale(2);
                item->setPosition(init_x, init_y);
                this->addChild(item);
           
                auto myLabel = Label::createWithSystemFont(std::to_string(num), "Arial", 20);
                myLabel->setPosition(Vec2(init_x_num, init_y_num));
                myLabel->setVisible(true);
                this->addChild(myLabel);
           
            }
            else if (id == SICKLE) {                      //镰刀的有关显示信息
                auto item = Sprite::create("sickle.png");
                item->setAnchorPoint(Vec2(0.5, 0.5));
                item->setScale(2);
                item->setPosition(init_x, init_y);
                this->addChild(item);

                auto myLabel = Label::createWithSystemFont(std::to_string(num), "Arial", 20);
                myLabel->setPosition(Vec2(init_x_num, init_y_num));
                myLabel->setVisible(true);
                this->addChild(myLabel);
            }
            else if (id == SEED) {                        //种子的有关显示信息
                auto item = Sprite::create("seed.png");
                item->setAnchorPoint(Vec2(0.5, 0.5));
                item->setScale(2);
                item->setPosition(init_x, init_y);
                this->addChild(item);

                auto myLabel = Label::createWithSystemFont(std::to_string(num), "Arial", 20);
                myLabel->setPosition(Vec2(init_x_num, init_y_num));
                myLabel->setVisible(true);
                this->addChild(myLabel);
            }
            else if (id == STONE) {                       //矿石的有关显示信息
                auto item = Sprite::create("stone.png");
                item->setAnchorPoint(Vec2(0.5, 0.5));
                item->setScale(2);
                item->setPosition(init_x, init_y);
                this->addChild(item);

                auto myLabel = Label::createWithSystemFont(std::to_string(num), "Arial", 20);
                myLabel->setPosition(Vec2(init_x_num, init_y_num));
                myLabel->setVisible(true);
                this->addChild(myLabel);
            }
            else if (id == CROP) {                        //庄稼的有关显示信息
                auto item = Sprite::create("crop.png");
                item->setAnchorPoint(Vec2(0.5, 0.5));
                item->setScale(2);
                item->setPosition(init_x, init_y);
                this->addChild(item);

                auto myLabel = Label::createWithSystemFont(std::to_string(num), "Arial", 20);
                myLabel->setPosition(Vec2(init_x_num, init_y_num));
                myLabel->setVisible(true);
                this->addChild(myLabel);
            }
        }
    }

    //设置返回菜单
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

//关闭背包
void Bag::close(Ref* obj) {         //切换场景
    Director::getInstance()->popScene();
}
