#include "ChartLayer.h"

USING_NS_CC;

// 构造函数
ChartLayer::ChartLayer() : currentNPC(nullptr) {}

// 析构函数
ChartLayer::~ChartLayer() {}

ChartLayer* ChartLayer::create(NPC* npc)
{
    ChartLayer* layer = new (std::nothrow) ChartLayer();
    if (layer && layer->init(npc))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool ChartLayer::init(NPC* npc)
{
    if (!Layer::init())
    {
        return false;
    }

    // 设置当前 NPC
    currentNPC = npc;

    Size winSize = Director::getInstance()->getWinSize();

    // 创建背景
    auto background = Sprite::create("chat_background.png");
    background->setContentSize(Size(winSize.width * 0.8f, winSize.height * 0.3f));
    background->setPosition(winSize.width / 2, winSize.height * 0.2f);
    this->addChild(background, 0, "chat_background");

    // 创建对话文本标签
    auto dialogLabel = Label::createWithTTF(currentNPC->getCurrentDialogue(), "fonts/Marker Felt.ttf", 24);
    dialogLabel->setAnchorPoint(Vec2(0, 1));
    dialogLabel->setPosition(Vec2(50, background->getPositionY() + background->getContentSize().height / 2 - 20));
    dialogLabel->setTextColor(Color4B::WHITE);
    this->addChild(dialogLabel, 1, "dialog_label");

    // 创建推进对话按钮
    auto nextButton = MenuItemLabel::create(
        Label::createWithTTF("Next", "fonts/Marker Felt.ttf", 20),
        CC_CALLBACK_1(ChartLayer::onNextButtonClicked, this)
    );
    nextButton->setPosition(Vec2(winSize.width * 0.7f, background->getPositionY() - background->getContentSize().height / 2 - 30));

    // 创建退出按钮
    auto quitButton = MenuItemLabel::create(
        Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 20),
        CC_CALLBACK_1(ChartLayer::onQuitButtonClicked, this)
    );
    quitButton->setPosition(Vec2(winSize.width * 0.3f, background->getPositionY() - background->getContentSize().height / 2 - 30));

    // 创建菜单并添加按钮
    auto menu = Menu::create(nextButton, quitButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

    return true;
}

void ChartLayer::updateDialog()
{
    // 获取对话标签
    auto dialogLabel = dynamic_cast<Label*>(this->getChildByName("dialog_label"));
    if (dialogLabel)
    {
        currentNPC->advanceDialogue(); // 推进 NPC 的对话
        dialogLabel->setString(currentNPC->getCurrentDialogue());
    }
}

void ChartLayer::closeChat()
{
    // 重置 NPC 的对话索引
    currentNPC->resetDialogue();
    this->removeFromParentAndCleanup(true);
}

void ChartLayer::onNextButtonClicked(Ref* sender)
{
    updateDialog(); // 更新对话内容
}

void ChartLayer::onQuitButtonClicked(Ref* sender)
{
    closeChat(); // 关闭聊天界面
}
