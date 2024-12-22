#include"ShoppingScene.h"
#include "Character.h"
#include<stdio.h>

Inventory ShoppingScene::shopgoods;
std::vector<int> ShoppingScene::prices;

ShoppingScene::ShoppingScene()
{
	nowSelected = 1;
#ifndef READ_FILE//如果不读档
	goodsTypeNum = 5;
	prices.resize(goodsTypeNum + 1);

	/* 暂时测试 */
	for (auto& v : prices)v = 30;
	for (int i = 1; i <= goodsTypeNum; ++i)shopgoods.Add_Item(i, 2);
#endif	
	toggles.resize(goodsTypeNum + 1);
}

Scene* ShoppingScene::createScene()
{
	return ShoppingScene::create();
}

bool ShoppingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	float gap = 0.01f * visibleSize.height; 
	float h = (visibleSize.height - (goodsTypeNum + 2) * gap) / (goodsTypeNum + 1);//每一个toggle的高度

	//显示钱的标签

	//购买按钮
	auto buyItem = MenuItemImage::create("buyItemNormal.png", "buyItemSelected.png", CC_CALLBACK_1(ShoppingScene::buyItem, this));
	buyItem->setAnchorPoint(Vec2(0, 0));
	buyItem->setPosition(Vec2(0.05f * visibleSize.width, gap));

	//退出商店按钮
	auto closeItem = MenuItemImage::create("closeShopNormal.png", "closeShopSelected.png", CC_CALLBACK_1(ShoppingScene::closeShoppingScene, this));
	closeItem->setAnchorPoint(Vec2(1, 0));
	closeItem->setPosition(Vec2(0.95f * visibleSize.width, gap));
		
	//创建一个菜单
	auto menu = Menu::create(buyItem, closeItem, NULL);

	//创建多个商品选项
	createToggles();

	//默认第一个商品显示选中
	//商品不同种类的 ID 从1开始 1、2、3···直到 goodsTypeNum
	toggles[1]->setSelectedIndex(1);
	toggles[1]->setEnabled(false);
	nowSelected = 1;

	//把所有toggle加入menu
	for (int i = 1; i <= goodsTypeNum; ++i) 
	{
		menu->addChild(toggles[i]);
	}

	//把menu加入ShoppingScene
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

MenuItemToggle* ShoppingScene::createAToggle(
	SEL_MenuHandler selector,char* itemNormalName, char* itemSelectedName, char* itemSoldOutName)
{
	auto itemNormal = MenuItemImage::create(itemNormalName, itemSelectedName);
	auto itemSelected = MenuItemImage::create(itemSelectedName, itemNormalName);
	auto itemSoldOut = MenuItemImage::create(itemSoldOutName, itemSoldOutName);
	auto toggle = MenuItemToggle::createWithTarget(this, selector, itemNormal, itemSelected, itemSoldOut, NULL);
	return toggle;
}

void ShoppingScene::createToggles()
{
	int i;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float gap = 0.01f * visibleSize.height;
	float h = (visibleSize.height - (goodsTypeNum + 2) * gap) / (goodsTypeNum + 1);//每一个toggle的高度
	char itemNormalName[30];
	char itemSelectedName[30];
	char itemSoldOutName[30];
	for (i = 1; i <= goodsTypeNum; ++i)
	{
		sprintf(itemNormalName, "itemNormal_%d.png", i);
		sprintf(itemSelectedName, "itemSelected_%d.png", i);
		sprintf(itemSoldOutName, "itemSoldOut_%d.png", i);
		toggles[i] = createAToggle(
			menu_selector(ShoppingScene::toggleIsPressed), itemNormalName, itemSelectedName, itemSoldOutName);
		toggles[i]->setTag(i);
		toggles[i]->setScale(h / toggles[i]->getContentSize().height);
		toggles[i]->setAnchorPoint(Vec2(0.5, 0));
		toggles[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - (gap + h) * i));
	}
}

//当toggles[i]被按下
void ShoppingScene::toggleIsPressed(Ref* obj)
{
	MenuItemToggle* pobj = (MenuItemToggle*)obj;
	if (shopgoods.Check_Item(pobj->getTag()) != -1)// ID == pobj->getTag() 的商品还有库存
	{
		pobj->setSelectedIndex(1);//设置为选中状态
		pobj->setEnabled(false);
		toggles[nowSelected]->setEnabled(true);
		toggles[nowSelected]->setSelectedIndex(0);//恢复为未选中状态
		
		nowSelected = pobj->getTag();
	}
}

void ShoppingScene::buyItem(Ref* pSender)
{
	int tmpMoney = Character::getInstance().get_money();
	// ID == nowSelected 的商品还有库存且价格 <= 主角拥有的钱
	if (shopgoods.Check_Item(nowSelected) != -1 &&
		prices[nowSelected] <= tmpMoney)
	{
		shopgoods.Remove_Item(nowSelected);//库存减1
		Character::getInstance().Remove_Item(MONEY, prices[nowSelected]);
		Character::getInstance().Get_Item(nowSelected + 10);
		if(shopgoods.Check_Item(nowSelected) == -1)//没有库存
		{
			toggles[nowSelected]->setSelectedIndex(2);//显示sold out图片
			toggles[nowSelected]->setEnabled(false);
			for (int i = 1; i <= goodsTypeNum; ++i)//循环找到一个有库存的商品
			{
				if (shopgoods.Check_Item(i) != -1)
				{
					toggles[i]->setSelectedIndex(1);//显示选中状态
					toggles[i]->setEnabled(false);
				}
			}
		}

		Character::getInstance().set_money(tmpMoney - prices[nowSelected]);
	}
}

void ShoppingScene::menuCloseCallback(Ref* pSender)
{ 
	Director::getInstance()->end();
}

void ShoppingScene::closeShoppingScene(Ref* pSender)
{
	Director::getInstance()->popScene();
}
