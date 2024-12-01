#include <iostream>
#include <vector>
#include "Inventory.h"

const int STACK_MAX = 9999;

struct item_in_storage                         //容器中的物品堆位置与数量
{
	int place;
	int num;
};

bool Inventory::Add_Item(Item &new_item)
{
	for (int i = 0; i < storage.size();++i)                  //遍历容器，查看是否有待存入物品的物品堆
	{
		if (storage[i].ID == new_item.ID&&storage[i].type != 1 && storage[i].num<STACK_MAX)  //如果有
		{
			if (new_item.num + storage[i].num <= STACK_MAX)      //物品堆能放下所有待存入物品
			{
				storage[i].num += new_item.num;                  //物品堆数量更新
				new_item.num = 0;                                //待存入物品减少到0
				return true;
			}
			else                                                //这一物品堆不能放下所有存入物品
			{
				new_item.num -= (STACK_MAX - storage[i].num);   //将待存入物品减去已存入的量
				storage[i].num = STACK_MAX;                     //存入的物品堆数量达到上限
			}
		}
	}
	if (new_item.num == 0)                                      //如果物品堆已经被全部存下
		return true;
	if (storage.size() < max_size - 1)                          //遍历所有已有物品堆后，还是没有放下所有待存入物品，则检查容器中是否有空间以新建物品堆
	{
		storage.push_back(new_item);                            //新建物品堆
		return true;
	}
	return false;                                               //放不下所有待存入物品
}
bool Inventory::Check_Item(Item& target_item, std::vector<item_in_storage>& found_items)
{
	int num = 0;
	for (int i = 0; i < storage.size(); ++i)                    //遍历所有物品堆，查看是否有所寻找物品
	{
		if (storage[i].ID == target_item.ID)
		{
			num += storage[i].num;                              //计算总量
			found_items.push_back({ i, num });                  //记录每一个物品堆的位置
		}
	}
	if (num >= target_item.num)                                 //总量足够
		return true;
	return false;
}
bool Inventory::Remove_Item(Item removing)
{
	std::vector<item_in_storage> found_items;
	if (!Check_Item(removing, found_items))                     //先检查是否有足够的物品
		return false;
	int min = min_stack(found_items);                           //找到数量最少的一个物品堆
	while (removing.num > 0)
	{
		if (found_items[min].num > removing.num)                //最少的一堆已经足以满足需求且有盈余
		{
			storage[found_items[min].place].num -= removing.num;
			return true;
		}
		else if (found_items[min].num == removing.num)         //最少的一堆刚好足以满足需求，将这一堆删除
		{
			storage.erase(storage.begin() + found_items[min].place);
			return true;
		}
		else                                                   //最少的一堆不足以满足需求，将这一堆删除，并从需求中减去已被满足的部分
		{
			removing.num -= found_items[min].num;
			storage.erase(storage.begin() + found_items[min].place);
			found_items.erase(found_items.begin() + min);
			min = min_stack(found_items);
		}
	}
	return true;
}

int Inventory::min_stack(std::vector<item_in_storage>& found_items)
{
	int min_stack = 0;
	for (int i = 1; i < found_items.size(); ++i)
	{
		min_stack = found_items[i].num < found_items[min_stack].num ? i : min_stack;
	}
	return min_stack;
}