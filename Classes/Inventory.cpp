#include <iostream>
#include <vector>
#include "Inventory.h"

const int STACK_MAX = 9999;

struct item_in_storage                         //�����е���Ʒ��λ��������
{
	int place;
	int num;
};

bool Inventory::Add_Item(Item &new_item)
{
	for (int i = 0; i < storage.size();++i)                  //�����������鿴�Ƿ��д�������Ʒ����Ʒ��
	{
		if (storage[i].ID == new_item.ID&&storage[i].type != 1 && storage[i].num<STACK_MAX)  //�����
		{
			if (new_item.num + storage[i].num <= STACK_MAX)      //��Ʒ���ܷ������д�������Ʒ
			{
				storage[i].num += new_item.num;                  //��Ʒ����������
				new_item.num = 0;                                //��������Ʒ���ٵ�0
				return true;
			}
			else                                                //��һ��Ʒ�Ѳ��ܷ������д�����Ʒ
			{
				new_item.num -= (STACK_MAX - storage[i].num);   //����������Ʒ��ȥ�Ѵ������
				storage[i].num = STACK_MAX;                     //�������Ʒ�������ﵽ����
			}
		}
	}
	if (new_item.num == 0)                                      //�����Ʒ���Ѿ���ȫ������
		return true;
	if (storage.size() < max_size - 1)                          //��������������Ʒ�Ѻ󣬻���û�з������д�������Ʒ�������������Ƿ��пռ����½���Ʒ��
	{
		storage.push_back(new_item);                            //�½���Ʒ��
		return true;
	}
	return false;                                               //�Ų������д�������Ʒ
}
bool Inventory::Check_Item(Item& target_item, std::vector<item_in_storage>& found_items)
{
	int num = 0;
	for (int i = 0; i < storage.size(); ++i)                    //����������Ʒ�ѣ��鿴�Ƿ�����Ѱ����Ʒ
	{
		if (storage[i].ID == target_item.ID)
		{
			num += storage[i].num;                              //��������
			found_items.push_back({ i, num });                  //��¼ÿһ����Ʒ�ѵ�λ��
		}
	}
	if (num >= target_item.num)                                 //�����㹻
		return true;
	return false;
}
bool Inventory::Remove_Item(Item removing)
{
	std::vector<item_in_storage> found_items;
	if (!Check_Item(removing, found_items))                     //�ȼ���Ƿ����㹻����Ʒ
		return false;
	int min = min_stack(found_items);                           //�ҵ��������ٵ�һ����Ʒ��
	while (removing.num > 0)
	{
		if (found_items[min].num > removing.num)                //���ٵ�һ���Ѿ�����������������ӯ��
		{
			storage[found_items[min].place].num -= removing.num;
			return true;
		}
		else if (found_items[min].num == removing.num)         //���ٵ�һ�Ѹպ������������󣬽���һ��ɾ��
		{
			storage.erase(storage.begin() + found_items[min].place);
			return true;
		}
		else                                                   //���ٵ�һ�Ѳ������������󣬽���һ��ɾ�������������м�ȥ�ѱ�����Ĳ���
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