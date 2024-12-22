#include"Character.h"

void Character::Get_Item(int id, int sum) {
	inventory.Add_Item(id, sum);
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

int Character::get_money()
{
	return money;
}

void Character::set_money(int _Money)
{
	money = _Money;
}
