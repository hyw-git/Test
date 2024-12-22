#ifndef __CHARACTER_H_
#define __CHARACTER_H
#include "cocos2d.h"
#include "Inventory.h"
USING_NS_CC;

class Character {
	friend class Archive;
private:
	int tool;     //�ֳֵĹ���
	float speed;  //�ƶ��ٶ�
	float hunger; //������
	float water;  //��ˮ��
	Inventory inventory;

	int money;//Ǯ

public:
	Character(){
#ifndef READ_FILE
		hunger = 10; water = 10;
		tool = 0;
		speed = 0;
		inventory.Add_Item(HOE);
		inventory.Add_Item(SEED, 100);
		inventory.Add_Item(SICKLE);
		money = 100;
#endif
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
   
	int get_money();
	void set_money(int);
};
#endif //