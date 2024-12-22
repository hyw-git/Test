#include"Character.h"

void Character::Get_Item(int id, int sum) {
	inventory.Add_Item(id, sum);
}

void Character::Remove_Item(int id, int num) {
	for (int ix = 0; ix < num; ix++) {
		inventory.Remove_Item(id);
	}
}

bool Character::Get_Message(int site, int& id, int& num) {
	return inventory.Get_Message(site, id, num);
}

int Character::Get_cus() {
	return inventory.Get_cus();
}

float Character::get_speed() {
	return speed;
}

void Character::set_speed(float Speed) {
	speed = Speed;
}

int Character::get_tool() {
	return tool;
}

void Character::set_tool(int Tool) {
	tool = Tool;
}

bool Character::Has_Hoe() {
	return (inventory.Check_Item(HOE) != -1);
}

bool Character::Has_Seed() {
	return (inventory.Check_Item(SEED) != -1);
}

bool Character::Has_Sickle() {
	return (inventory.Check_Item(SICKLE) != -1);
}

bool Character::Has_Stone() {
	return (inventory.Check_Item(STONE) != -1);
}

bool Character::Has_CROP(int num) {
	int id;
	int sum;
	inventory.Get_Message(inventory.Check_Item(CROP), id, sum);
	return (sum >= num);
}
