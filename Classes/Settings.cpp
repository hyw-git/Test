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

//初始化设置场景
bool Settings::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
	//预加载背景音乐
	audio = SimpleAudioEngine::getInstance();//获取当前音频状态
	audio->preloadBackgroundMusic("Statdew_Valley_Overture.mp3");//预加载背景音乐

	//可视化的窗口宽高
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//原点坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片精灵
	auto SettingsBG = Sprite::create("SettingsBG.jpeg");
	SettingsBG->setAnchorPoint(Vec2(0.5, 0.5));//锚点是中心
	SettingsBG->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y));//背景图片放在正中间
	SettingsBG->setScale(1.1, 1.1);//X、Y都放大为1.1倍
	this->addChild(SettingsBG);

	//创建标题"SETTINGS"标签
	auto titleLabel = Label::createWithSystemFont("SETTINGS", "arial", 70);
	titleLabel->setColor(Color3B(255, 255, 0));
	titleLabel->enableShadow();
	titleLabel->setPosition(Vec2(
		visibleSize.width / 64*43 + origin.x, 
		visibleSize.height / 16 * 13 + origin.y));
	this->addChild(titleLabel);//加入场景图，显示在界面上


	//创建"开启和关闭音量"的按钮
	volumeOffItem = MenuItemImage::create("volumeOff.png", "volumeOn.png");
    volumeOnItem = MenuItemImage::create("volumeOn.png", "volumeOff.png");
	MenuItemToggle* volumeOnOffToggle;//菜单项的选择器
	if (audio->isBackgroundMusicPlaying())//判断当前是否正在播放音乐
	{
		volumeOnOffToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(Settings::volumeOnOffCallback, this),
			volumeOnItem,
			volumeOffItem,
			NULL);//利用Toggle实现两个菜单项的切换， MenuItemToggle管理当前应该显示的菜单项
	}
	else
	{
		volumeOnOffToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(Settings::volumeOnOffCallback, this),
			volumeOffItem,
			volumeOnItem,
			NULL);//利用Toggle实现两个菜单项的切换， MenuItemToggle管理当前应该显示的菜单项
	}
	volumeOnOffToggle->setAnchorPoint(Vec2(0.5, 0.5));//锚点是中心
	volumeOnOffToggle->setPosition(Vec2(
		visibleSize.width / 2 + origin.x, 
		visibleSize.height / 2 + origin.y-130));
	volumeOnOffToggle->setScale(1.35, 1.35);


	//创建一个音量条
	volumeSlider = ui::Slider::create();
	volumeSlider->loadBarTexture("SliderBack.png"); // 背景底条
	volumeSlider->loadSlidBallTextures("SliderNodeNormal.png", "SliderNodeSliding.png", "SliderNodeDisabled.png");//滑动方块
	volumeSlider->loadProgressBarTexture("SliderPressBar.png");//进度条
	//音量条的 位置
	volumeSlider->setAnchorPoint(Vec2(0.5, 0.5));
	volumeSlider->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y - 200));
	//音量大小的值
	float volumeValue = audio->getBackgroundMusicVolume();//需要重写这个虚函数
	//设置音量条滑动方块的初始位置
	volumeSlider->setPercent(volumeValue * 100.0f);
	if (audio->isBackgroundMusicPlaying())volumeSlider->setEnabled(1); else volumeSlider->setEnabled(0);
	//添加事件监听器
	volumeSlider->addEventListener(
		[&](Ref* pSender, ui::Slider::EventType type)
		{
			if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				volumeValue = volumeSlider->getPercent() * 0.01f;
				//audio->setBackgroundMusicVolume(volumeValue);//还没实现调节音量的功能，需要重写这个虚函数
			}
		});

	this->addChild(volumeSlider);

	//创建右下角的退出设置菜单项
	auto exitSettingsItem = MenuItemImage::create(
		"exitSettingsNormal.png", 
		"exitSettingsSelected.png",
		CC_CALLBACK_1(Settings::exitSettings,this)); 
	titleLabel->setAnchorPoint(Vec2(1, 0));
	exitSettingsItem->setScale(1.5,1.5);
	exitSettingsItem->setPosition(Vec2(
		visibleSize.width - exitSettingsItem->getContentSize().width ,
		exitSettingsItem->getContentSize().height));
	
	//存档按钮
	auto archiveItem= MenuItemImage::create(
		"archive.png",
		"archiveSelected.png",
		CC_CALLBACK_1(Settings::archiveGame, this));
	archiveItem->setAnchorPoint(Vec2(0.5, 0.5));
	archiveItem->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y - 30));
	archiveItem->setScale(1.25);

	//商店按钮/*****/用作测试
	auto shopItem = MenuItemImage::create("shopItemNormal.png", "shopItemSelected.png", CC_CALLBACK_1(Settings::shopItem, this));
	shopItem->setAnchorPoint(Vec2(0.5, 0.5));
	shopItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+100));

	//创建菜单
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
//退出设置场景
void Settings::exitSettings(Ref* obj)
{
	Director::getInstance()->popScene();
}

//打开音量
void Settings::volumeTurnOn()
{
	//获取音频对象，这是一个单例对象
	auto audio = SimpleAudioEngine::getInstance();
	//设置背景音乐，并且持续播放
	audio->playBackgroundMusic("Statdew_Valley_Overture.mp3", true);
}

//关闭音量
void Settings::volumeTurnOff()
{
	//获取音频对象，就是上面那个对象
	auto audio = SimpleAudioEngine::getInstance();
	//停止播放背景音乐
	audio->stopBackgroundMusic();
}

//决定当前是打开音量还是关闭音量
void Settings::volumeOnOffCallback(Ref* obj)
{
	MenuItemToggle* toggle = dynamic_cast<MenuItemToggle*>(obj);
	if (toggle->getSelectedItem() == volumeOnItem)
	{
		// 当前状态是volumeOn，打开音乐
		volumeTurnOn();
		volumeSlider->setEnabled(true);
	}
	else if (toggle->getSelectedItem() == volumeOffItem)
	{
		// 当前状态是volumeOff，关闭音乐
		volumeTurnOff();
		volumeSlider->setEnabled(false);
	}
}

//存档游戏
void Settings::archiveGame(Ref* obj)
{
	Archive::getInstance()->SaveGame();
}

void Settings::shopItem(Ref* obj)
{
	/* 进行商店测试 */
	auto shopScene = ShoppingScene::createScene();
	Director::getInstance()->pushScene(shopScene);
}

