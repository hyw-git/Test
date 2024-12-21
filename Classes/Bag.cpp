#include "Bag.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using std::to_string;

//����һ����������
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

//��½�����ʼ��
bool Bag::init()
{
    if (!Scene::init())
        return false;

    //��������ͼƬ����
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spriteBack = Sprite::create("bag.png");               //�������ͼƬ
    auto background = Sprite::create("Begin.png");             //��������ͼƬ

    //����ͼƬλ��
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background);

    //����ͼƬλ��
    spriteBack->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(spriteBack);

    //��ȡ������Ϣ
    int id, cus, num;                         //��Ʒid����������������
    int init_x = 220, init_y = 470;           //��ʼͼƬ����λ��
    int init_x_num = 250, init_y_num = 445;   //��ʼ���ֻ���λ��
    cus = character.Get_cus();                //��ȡ������������
    if (cus != -1) {
        for (int ix = 0; ix < cus; ix++, init_x += 75, init_x_num += 75) {
            character.Get_Message(ix, id, num);           //��ȡÿһ���е���Ʒ��Ϣ
            if (id == HOE) {                              //��ͷ���й���ʾ��Ϣ
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
            else if (id == SICKLE) {                      //�������й���ʾ��Ϣ
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
            else if (id == SEED) {                        //���ӵ��й���ʾ��Ϣ
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
            else if (id == STONE) {                       //��ʯ���й���ʾ��Ϣ
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
            else if (id == CROP) {                        //ׯ�ڵ��й���ʾ��Ϣ
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

    //���÷��ز˵�
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

//�رձ���
void Bag::close(Ref* obj) {         //�л�����
    Director::getInstance()->popScene();
}
