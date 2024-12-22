#ifndef __INVENTORY_H__
#define __INVENTORY_H__


#include <vector>
#include "Def.h"
//#include "Archive.h"

struct Item                                  //物品堆
{
	int ID;                                 //物品的ID
	int num;                                //物品的数量
};

class Inventory
{
	friend class Archive;
private:
	std::vector<Item> storage;              //用于储存容器中物品的信息
	int cus;
	int max_size;                           //用于储存容器的最大容量
	int maxsize;                            //用于存储每一堆的最大容量
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(CAPACITY_OF_STORAGE_IN_INVENTORY){}
    bool Add_Item(int id, int sum = 1);
	int Check_Item(int id);
	bool Remove_Item(int id);
};
#endif // !__INVENTORY_H__