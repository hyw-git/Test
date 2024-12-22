#ifndef __INVENTORY_H__
#define __INVENTORY_H__


#include <vector>
#include "Def.h"
//#include "Archive.h"

struct Item                                  //��Ʒ��
{
	int ID;                                 //��Ʒ��ID
	int num;                                //��Ʒ������
};

class Inventory
{
	friend class Archive;
private:
	std::vector<Item> storage;              //���ڴ�����������Ʒ����Ϣ
	int cus;
	int max_size;                           //���ڴ����������������
	int maxsize;                            //���ڴ洢ÿһ�ѵ��������
public:
	Inventory(): cus(0), max_size(99), maxsize(999), storage(CAPACITY_OF_STORAGE_IN_INVENTORY){}
	bool Add_Item(int id, int sum = 1);     //������Ʒ
	int Check_Item(int id);                 //������Ʒ
	bool Remove_Item(int id);               //�Ƴ���Ʒ
	int Get_cus();                          //���ص�ǰռ�õĸ�����
	bool Get_Message(int site, int& id, int& num);   //��ȡ��Ʒ��Ϣ
};
#endif // !__INVENTORY_H__