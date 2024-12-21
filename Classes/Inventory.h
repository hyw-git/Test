#pragma once
#include <vector>
#include "Def.h"

struct Item                                  
{
	int ID;                                 //��Ʒ��ID
	int num;                                //��Ʒ������
};

class Inventory
{
private:
	std::vector<Item> storage;              //���ڴ�����������Ʒ����Ϣ
	int cus;                                //��ǰռ�õĸ�����
	int max_size;                           //�ܸ�����
	int maxsize;                            //ÿ����������
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(99){}
	bool Add_Item(int id, int sum = 1);     //������Ʒ
	int Check_Item(int id);                 //������Ʒ
	bool Remove_Item(int id);               //�Ƴ���Ʒ
	int Get_cus();                          //���ص�ǰռ�õĸ�����
	bool Get_Message(int site, int& id, int& num);   //��ȡ��Ʒ��Ϣ
};
