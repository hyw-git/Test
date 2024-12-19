#pragma once
#include <vector>
#include "Def.h"

struct Item                                  //��Ʒ��
{
	int ID;                                 //��Ʒ��ID
	int num;                                //��Ʒ������
};

class Inventory
{
private:
	std::vector<Item> storage;              //���ڴ�����������Ʒ����Ϣ
	int cus;
	int max_size;                           //���ڴ����������������
	int maxsize;
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(999){}
	bool Add_Item(int id, int sum = 1);
	int Check_Item(int id);
	bool Remove_Item(int id);
};
