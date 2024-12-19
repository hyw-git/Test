#pragma once
#include <vector>
#include "Def.h"

struct Item                                  //物品堆
{
	int ID;                                 //物品的ID
	int num;                                //物品的数量
};

class Inventory
{
private:
	std::vector<Item> storage;              //用于储存容器中物品的信息
	int cus;
	int max_size;                           //用于储存容器的最大容量
	int maxsize;
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(999){}
	bool Add_Item(int id, int sum = 1);
	int Check_Item(int id);
	bool Remove_Item(int id);
};
