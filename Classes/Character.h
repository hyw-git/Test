#include "cocos2d.h"
#include "Inventory.h"
USING_NS_CC;

class Character {
private:
	int tool;     //�ֳֵĹ���
	float speed;  //�ƶ��ٶ�
	float hunger; //������
	float water;  //��ˮ��
	Inventory inventory;

public:
	Character():hunger(10), water(10) {         //���캯��
		tool = 0;
		speed = 40.0f;                          //��ʼ�ٶ�40.0
		inventory.Add_Item(HOE);                //��ʼ��ͷ*1
		inventory.Add_Item(SEED, 50);           //��ʼ����*50
	}
	static Character& getInstance() {           //����ʵ��
		static Character character;
		return character;
	}
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

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
};