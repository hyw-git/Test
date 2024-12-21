#pragma once
#include <vector>
#include "Def.h"

struct Item                                  
{
	int ID;                                 //物品的ID
	int num;                                //物品的数量
};

class Inventory
{
private:
	std::vector<Item> storage;              //用于储存容器中物品的信息
	int cus;                                //当前占用的格子数
	int max_size;                           //总格子数
	int maxsize;                            //每格的最大容量
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(99){}
	bool Add_Item(int id, int sum = 1);     //加入物品
	int Check_Item(int id);                 //查找物品
	bool Remove_Item(int id);               //移除物品
	int Get_cus();                          //返回当前占用的格子数
	bool Get_Message(int site, int& id, int& num);   //获取物品信息
};
