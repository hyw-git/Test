#pragma once
#include <iostream>
#include <vector>
class Item                                  //物品堆
{
	int ID;                                 //物品的ID
	int type;                               //物品的类型（目前只有工具被特殊考虑）
	int num;                                //物品的数量
	friend Inventory;
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