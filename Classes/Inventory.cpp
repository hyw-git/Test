#include <iostream>
#include <vector>
#include "Inventory.h"

bool Inventory::Add_Item(int id, int sum)
{
	int site = Check_Item(id);
	if (site == -1) {
		if (cus != max_size) {
			storage[cus].ID = id;
			storage[cus].num += sum;
			cus++;
			return true;
		}
		else
			return false;
	}

	else {
		if (storage[site].num == maxsize && cus != max_size) {
			storage[cus].ID = id;
			storage[cus].num += sum;
			cus++;
			return true;
		}
		else if (storage[site].num < maxsize) {
			storage[site].num += sum;
			return true;
		}
		else
			return false;
	}
}

int Inventory::Check_Item(int id)
{
	int site = -1;
	for (int i = 0; i < cus; ++i)
	{
		if (storage[i].ID == id)
			site = i;
	}
	return site;
}

bool Inventory::Remove_Item(int id)
{
	const int status = Check_Item(id);
	if (status == -1)
		return false;
	else {
		storage[status].num--;
		return true;
	}
}

int Inventory::Get_cus() {
	return cus;
}

bool Inventory::Get_Message(int site, int& id, int& num) {
	if (site >= cus)
		return false;
	id = storage[site].ID;
	num = storage[site].num;
	return true;
}
