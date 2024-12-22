#ifndef __CHARACTER_H_
#define __CHARACTER_H
#include "cocos2d.h"
#include "Inventory.h"
USING_NS_CC;

class Character {
	friend class Archive;
private:
	int tool;     //手持的工具
	float speed;  //移动速度
	float hunger; //饥饿度
	float water;  //需水量
	Inventory inventory;

	int money;//钱

public:
	Character(){
#ifndef READ_FILE
		hunger = 10; water = 10;
		tool = 0;
		speed = 0;
		inventory.Add_Item(HOE);
		inventory.Add_Item(SEED, 100);
		inventory.Add_Item(MONEY, 100);
		money = 100;
#endif
	}
	static Character& getInstance() {
		static Character character;
		return character;
	}
	void Get_Item(int id, int sum = 1);         //获得物品
	void Remove_Item(int id, int sum = 1);      //消耗并移除物品
	bool Get_Message(int site, int& id, int& num);  //获取物品信息
	int Get_cus();                              //获取背包已用格子数

	int get_tool();                             //获取手中持有的物品信息
	void set_tool(int tool);                    //设置手中物品
	//判断背包中是否有此类物品
	bool Has_Hoe();
	bool Has_Seed();
	bool Has_Sickle();
	bool Has_Stone();
	bool Has_CROP(int num);

	float get_speed();                          //获取角色移动属性
	void set_speed(float speed);                //设置角色移动属性
   
	int get_money();
	void set_money(int);
};
#endif //