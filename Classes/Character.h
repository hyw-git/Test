#include "cocos2d.h"
#include "Inventory.h"
USING_NS_CC;

class Character {
private:
	int tool;     //手持的工具
	float speed;  //移动速度
	float hunger; //饥饿度
	float water;  //需水量
	Inventory inventory;

public:
	Character():hunger(10), water(10) {
		tool = 0;
		speed = 0;
		inventory.Add_Item(HOE);
		inventory.Add_Item(SEED, 100);
		inventory.Add_Item(SICKLE);
	}
	static Character& getInstance() {
		static Character character;
		return character;
	}
	void Get_Item(int id, int sum = 1);

	int get_tool();
	void set_tool(int tool);
	bool Has_Hoe();
	bool Has_Seed();
	bool Has_Sickle();

	float get_speed();
	void set_speed(float speed);
};