#pragma once
#include <iostream>
#include <vector>

#define axe 1000
#define hoe 1100
#define seed 4225
class Item                                  //物品堆
{
private:
	int ID;                                 //物品的ID
	int num;                                //物品的数量
	friend Inventory;
public:
	Item(int sID, int snum) :ID(sID), num(snum) {};
	int Interaction();
};
class Inventory
{
private:
	std::vector<Item> storage;              //用于储存容器中物品的信息
	int max_size;                           //用于储存容器的最大容量
public:
	bool Add_Item(Item& new_item);
	bool Check_Item(Item& target_item, std::vector<item_in_storage>& found_items);
	bool Remove_Item(Item removing);
	inline int min_stack(std::vector<item_in_storage>& found_items);
};
