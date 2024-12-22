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
		inventory.Add_Item(MONEY, 100);
		money = 100;
#endif
	}
	static Character& getInstance() {
		static Character character;
		return character;
	}
	void Get_Item(int id, int sum = 1);         //�����Ʒ
	void Remove_Item(int id, int sum = 1);      //���Ĳ��Ƴ���Ʒ
	bool Get_Message(int site, int& id, int& num);  //��ȡ��Ʒ��Ϣ
	int Get_cus();                              //��ȡ�������ø�����

	int get_tool();                             //��ȡ���г��е���Ʒ��Ϣ
	void set_tool(int tool);                    //����������Ʒ
	//�жϱ������Ƿ��д�����Ʒ
	bool Has_Hoe();
	bool Has_Seed();
	bool Has_Sickle();
	bool Has_Stone();
	bool Has_CROP(int num);

	float get_speed();                          //��ȡ��ɫ�ƶ�����
	void set_speed(float speed);                //���ý�ɫ�ƶ�����
   
	int get_money();
	void set_money(int);
};
#endif //