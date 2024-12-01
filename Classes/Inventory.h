#pragma once
#include <iostream>
#include <vector>
class Item                                  //��Ʒ��
{
	int ID;                                 //��Ʒ��ID
	int type;                               //��Ʒ�����ͣ�Ŀǰֻ�й��߱����⿼�ǣ�
	int num;                                //��Ʒ������
	friend Inventory;
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