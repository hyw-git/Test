#pragma once
#include <iostream>
#include <vector>

#define axe 1000
#define hoe 1100
#define seed 4225
class Item                                  //��Ʒ��
{
private:
	int ID;                                 //��Ʒ��ID
	int num;                                //��Ʒ������
	friend Inventory;
public:
	Item(int sID, int snum) :ID(sID), num(snum) {};
	int Interaction();
};
class Inventory
{
private:
	std::vector<Item> storage;              //���ڴ�����������Ʒ����Ϣ
	int max_size;                           //���ڴ����������������
public:
	bool Add_Item(Item& new_item);
	bool Check_Item(Item& target_item, std::vector<item_in_storage>& found_items);
	bool Remove_Item(Item removing);
	inline int min_stack(std::vector<item_in_storage>& found_items);
};
