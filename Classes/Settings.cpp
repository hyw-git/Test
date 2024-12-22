#include "Settings.h"
#include "Archive.h"
#include "ShoppingScene.h"

USING_NS_CC;
using namespace CocosDenshion;

//
Scene* Settings::createSettingsScene()
{
	return Settings::create();
}

//��ʼ�����ó���
bool Settings::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
	//Ԥ���ر�������
	audio = SimpleAudioEngine::getInstance();//��ȡ��ǰ��Ƶ״̬
	audio->preloadBackgroundMusic("Statdew_Valley_Overture.mp3");//Ԥ���ر�������

	//���ӻ��Ĵ��ڿ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//ԭ������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//����ͼƬ����
	auto SettingsBG = Sprite::create("SettingsBG.jpeg");
	SettingsBG->setAnchorPoint(Vec2(0.5, 0.5));//ê��������
	SettingsBG->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y));//����ͼƬ�������м�
	SettingsBG->setScale(1.1, 1.1);//X��Y���Ŵ�Ϊ1.1��
	this->addChild(SettingsBG);

	//��������"SETTINGS"��ǩ
	auto titleLabel = Label::createWithSystemFont("SETTINGS", "arial", 70);
	titleLabel->setColor(Color3B(255, 255, 0));
	titleLabel->enableShadow();
	titleLabel->setPosition(Vec2(
		visibleSize.width / 64*43 + origin.x, 
		visibleSize.height / 16 * 13 + origin.y));
	this->addChild(titleLabel);//���볡��ͼ����ʾ�ڽ�����


	//����"�����͹ر�����"�İ�ť
	volumeOffItem = MenuItemImage::create("volumeOff.png", "volumeOn.png");
    volumeOnItem = MenuItemImage::create("volumeOn.png", "volumeOff.png");
	MenuItemToggle* volumeOnOffToggle;//�˵����ѡ����
	if (audio->isBackgroundMusicPlaying())//�жϵ�ǰ�Ƿ����ڲ�������
	{
		volumeOnOffToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(Settings::volumeOnOffCallback, this),
			volumeOnItem,
			volumeOffItem,
			NULL);//����Toggleʵ�������˵�����л��� MenuItemToggle����ǰӦ����ʾ�Ĳ˵���
	}
	else
	{
		volumeOnOffToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(Settings::volumeOnOffCallback, this),
			volumeOffItem,
			volumeOnItem,
			NULL);//����Toggleʵ�������˵�����л��� MenuItemToggle����ǰӦ����ʾ�Ĳ˵���
	}
	volumeOnOffToggle->setAnchorPoint(Vec2(0.5, 0.5));//ê��������
	volumeOnOffToggle->setPosition(Vec2(
		visibleSize.width / 2 + origin.x, 
		visibleSize.height / 2 + origin.y-130));
	volumeOnOffToggle->setScale(1.35, 1.35);


	//����һ��������
	volumeSlider = ui::Slider::create();
	volumeSlider->loadBarTexture("SliderBack.png"); // ��������
	volumeSlider->loadSlidBallTextures("SliderNodeNormal.png", "SliderNodeSliding.png", "SliderNodeDisabled.png");//��������
	volumeSlider->loadProgressBarTexture("SliderPressBar.png");//������
	//�������� λ��
	volumeSlider->setAnchorPoint(Vec2(0.5, 0.5));
	volumeSlider->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y - 200));
	//������С��ֵ
	float volumeValue = audio->getBackgroundMusicVolume();//��Ҫ��д����麯��
	//������������������ĳ�ʼλ��
	volumeSlider->setPercent(volumeValue * 100.0f);
	if (audio->isBackgroundMusicPlaying())volumeSlider->setEnabled(1); else volumeSlider->setEnabled(0);
	//����¼�������
	volumeSlider->addEventListener(
		[&](Ref* pSender, ui::Slider::EventType type)
		{
			if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				volumeValue = volumeSlider->getPercent() * 0.01f;
				//audio->setBackgroundMusicVolume(volumeValue);//��ûʵ�ֵ��������Ĺ��ܣ���Ҫ��д����麯��
			}
		});

	this->addChild(volumeSlider);

	//�������½ǵ��˳����ò˵���
	auto exitSettingsItem = MenuItemImage::create(
		"exitSettingsNormal.png", 
		"exitSettingsSelected.png",
		CC_CALLBACK_1(Settings::exitSettings,this)); 
	titleLabel->setAnchorPoint(Vec2(1, 0));
	exitSettingsItem->setScale(1.5,1.5);
	exitSettingsItem->setPosition(Vec2(
		visibleSize.width - exitSettingsItem->getContentSize().width ,
		exitSettingsItem->getContentSize().height));
	
	//�浵��ť
	auto archiveItem= MenuItemImage::create(
		"archive.png",
		"archiveSelected.png",
		CC_CALLBACK_1(Settings::archiveGame, this));
	archiveItem->setAnchorPoint(Vec2(0.5, 0.5));
	archiveItem->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y - 30));
	archiveItem->setScale(1.25);

	//�̵갴ť/*****/��������
	auto shopItem = MenuItemImage::create("shopItemNormal.png", "shopItemSelected.png", CC_CALLBACK_1(Settings::shopItem, this));
	shopItem->setAnchorPoint(Vec2(0.5, 0.5));
	shopItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+100));

	//�����˵�
	auto menu = Menu::create(exitSettingsItem, volumeOnOffToggle, archiveItem, shopItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

// a selector callback
void Settings:: menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}
//�˳����ó���
void Settings::exitSettings(Ref* obj)
{
	Director::getInstance()->popScene();
}

//������
void Settings::volumeTurnOn()
{
	//��ȡ��Ƶ��������һ����������
	auto audio = SimpleAudioEngine::getInstance();
	//���ñ������֣����ҳ�������
	audio->playBackgroundMusic("Statdew_Valley_Overture.mp3", true);
}

//�ر�����
void Settings::volumeTurnOff()
{
	//��ȡ��Ƶ���󣬾��������Ǹ�����
	auto audio = SimpleAudioEngine::getInstance();
	//ֹͣ���ű�������
	audio->stopBackgroundMusic();
}

//������ǰ�Ǵ��������ǹر�����
void Settings::volumeOnOffCallback(Ref* obj)
{
	MenuItemToggle* toggle = dynamic_cast<MenuItemToggle*>(obj);
	if (toggle->getSelectedItem() == volumeOnItem)
	{
		// ��ǰ״̬��volumeOn��������
		volumeTurnOn();
		volumeSlider->setEnabled(true);
	}
	else if (toggle->getSelectedItem() == volumeOffItem)
	{
		// ��ǰ״̬��volumeOff���ر�����
		volumeTurnOff();
		volumeSlider->setEnabled(false);
	}
}

//�浵��Ϸ
void Settings::archiveGame(Ref* obj)
{
	Archive::getInstance()->SaveGame();
}

void Settings::shopItem(Ref* obj)
{
	/* �����̵���� */
	auto shopScene = ShoppingScene::createScene();
	Director::getInstance()->pushScene(shopScene);
}

