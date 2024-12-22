#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include"Character.h"
//#include"Shop.h"
#include"Inventory.h"
//#include"GameTime.h"

struct InventoryContents 
{
    int save_cus;
    int save_max_size;                           //用于储存容器的最大容量
    int save_maxsize;                            //用于存储每一堆的最大容量
    Item save_items[CAPACITY_OF_STORAGE_IN_INVENTORY];  //capacity of vector in Inventory is 999不变
};

struct CharacterContentes 
{
    int save_tool;     //手持的工具
    float save_speed;  //移动速度
    float save_hunger; //饥饿度
    float save_water;  //需水量
    int save_money;    //钱
    InventoryContents  save_characterInventory;
};

struct ShopContentes 
{
    InventoryContents  save_shopInventory;

    //···
    //···
};

struct TimeContentes
{
    int hour;        //当前小时
    int minute;      //当前分钟
    bool running;    //时间是否在流逝
    float timeSpeed; //时间流速（现实 0.7 秒 = 游戏内 1 分钟）
};

//所有需要保存的内容放进一个结构体
struct Contents 
{
    CharacterContentes save_character;
    ShopContentes save_shop;
    TimeContentes save_time;    

    //···
    //···
};


class Archive
{
private:
    static FILE* pFile;
    static Contents *pContents;
    void CopyToContents();      //把所有需要保存的内容拷贝到结构体对象中
    void InitFromContents();    //把结构体对象的内容拷贝到其他类对象中
    Archive() {};
public:
    static Archive* getInstance()
    {
        static Archive archive;
        return &archive;
    }
    bool SaveGame(const char* s = ".\\game.bin");;  //存档
    bool ReadFile(const char* s = ".\\game.bin");    //读档
                             
   /* Contents* getContents();   */
};

#endif // __ARCHIVE_H__
