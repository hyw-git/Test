#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include"Character.h"
//#include"Shop.h"
#include"Inventory.h"
//#include"GameTime.h"

struct InventoryContents 
{
    int save_cus;
    int save_max_size;                           //���ڴ����������������
    int save_maxsize;                            //���ڴ洢ÿһ�ѵ��������
    Item save_items[CAPACITY_OF_STORAGE_IN_INVENTORY];  //capacity of vector in Inventory is 999����
};

struct CharacterContentes 
{
    int save_tool;     //�ֳֵĹ���
    float save_speed;  //�ƶ��ٶ�
    float save_hunger; //������
    float save_water;  //��ˮ��
    int save_money;    //Ǯ
    InventoryContents  save_characterInventory;
};

struct ShopContentes 
{
    InventoryContents  save_shopInventory;

    //������
    //������
};

struct TimeContentes
{
    int hour;        //��ǰСʱ
    int minute;      //��ǰ����
    bool running;    //ʱ���Ƿ�������
    float timeSpeed; //ʱ�����٣���ʵ 0.7 �� = ��Ϸ�� 1 ���ӣ�
};

//������Ҫ��������ݷŽ�һ���ṹ��
struct Contents 
{
    CharacterContentes save_character;
    ShopContentes save_shop;
    TimeContentes save_time;    

    //������
    //������
};


class Archive
{
private:
    static FILE* pFile;
    static Contents *pContents;
    void CopyToContents();      //��������Ҫ��������ݿ������ṹ�������
    void InitFromContents();    //�ѽṹ���������ݿ����������������
    Archive() {};
public:
    static Archive* getInstance()
    {
        static Archive archive;
        return &archive;
    }
    bool SaveGame(const char* s = ".\\game.bin");;  //�浵
    bool ReadFile(const char* s = ".\\game.bin");    //����
                             
   /* Contents* getContents();   */
};

#endif // __ARCHIVE_H__
