#include"ShoppingScene.h"
#include "Character.h"
#include<stdio.h>

Inventory ShoppingScene::shopgoods;
std::vector<int> ShoppingScene::prices;

ShoppingScene::ShoppingScene()
{
	nowSelected = 1;
#ifndef READ_FILE//���������
	goodsTypeNum = 5;
	prices.resize(goodsTypeNum + 1);

	/* ��ʱ���� */
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
	float h = (visibleSize.height - (goodsTypeNum + 2) * gap) / (goodsTypeNum + 1);//ÿһ��toggle�ĸ߶�

	//��ʾǮ�ı�ǩ

	//����ť
	auto buyItem = MenuItemImage::create("buyItemNormal.png", "buyItemSelected.png", CC_CALLBACK_1(ShoppingScene::buyItem, this));
	buyItem->setAnchorPoint(Vec2(0, 0));
	buyItem->setPosition(Vec2(0.05f * visibleSize.width, gap));

	//�˳��̵갴ť
	auto closeItem = MenuItemImage::create("closeShopNormal.png", "closeShopSelected.png", CC_CALLBACK_1(ShoppingScene::closeShoppingScene, this));
	closeItem->setAnchorPoint(Vec2(1, 0));
	closeItem->setPosition(Vec2(0.95f * visibleSize.width, gap));
		
	//����һ���˵�
	auto menu = Menu::create(buyItem, closeItem, NULL);

	//���������Ʒѡ��
	createToggles();

	//Ĭ�ϵ�һ����Ʒ��ʾѡ��
	//��Ʒ��ͬ����� ID ��1��ʼ 1��2��3������ֱ�� goodsTypeNum
	toggles[1]->setSelectedIndex(1);
	toggles[1]->setEnabled(false);
	nowSelected = 1;

	//������toggle����menu
	for (int i = 1; i <= goodsTypeNum; ++i) 
	{
		menu->addChild(toggles[i]);
	}

	//��menu����ShoppingScene
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
	float h = (visibleSize.height - (goodsTypeNum + 2) * gap) / (goodsTypeNum + 1);//ÿһ��toggle�ĸ߶�
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

//��toggles[i]������
void ShoppingScene::toggleIsPressed(Ref* obj)
{
	MenuItemToggle* pobj = (MenuItemToggle*)obj;
	if (shopgoods.Check_Item(pobj->getTag()) != -1)// ID == pobj->getTag() ����Ʒ���п��
	{
		pobj->setSelectedIndex(1);//����Ϊѡ��״̬
		pobj->setEnabled(false);
		toggles[nowSelected]->setEnabled(true);
		toggles[nowSelected]->setSelectedIndex(0);//�ָ�Ϊδѡ��״̬
		
		nowSelected = pobj->getTag();
	}
}

void ShoppingScene::buyItem(Ref* pSender)
{
	int tmpMoney = Character::getInstance().get_money();
	// ID == nowSelected ����Ʒ���п���Ҽ۸� <= ����ӵ�е�Ǯ
	if (shopgoods.Check_Item(nowSelected) != -1 &&
		prices[nowSelected] <= tmpMoney)
	{
		shopgoods.Remove_Item(nowSelected);//����1
		Character::getInstance().Remove_Item(MONEY, prices[nowSelected]);
		Character::getInstance().Get_Item(nowSelected + 10);
		if(shopgoods.Check_Item(nowSelected) == -1)//û�п��
		{
			toggles[nowSelected]->setSelectedIndex(2);//��ʾsold outͼƬ
			toggles[nowSelected]->setEnabled(false);
			for (int i = 1; i <= goodsTypeNum; ++i)//ѭ���ҵ�һ���п�����Ʒ
			{
				if (shopgoods.Check_Item(i) != -1)
				{
					toggles[i]->setSelectedIndex(1);//��ʾѡ��״̬
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
