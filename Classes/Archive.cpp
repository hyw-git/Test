#include "Archive.h"
#include <stdio.h>
#include <string.h>

FILE* Archive::pFile = NULL;
static Contents contents;
Contents* Archive::pContents = &contents;

inline void Archive::CopyToContents()
{
	//save_character
	pContents->save_character.save_tool = Character::getInstance().tool;
	pContents->save_character.save_speed = Character::getInstance().speed;
	pContents->save_character.save_hunger= Character::getInstance().hunger;
	pContents->save_character.save_water = Character::getInstance().water;
	pContents->save_character.save_money = Character::getInstance().money;
	pContents->save_character.save_characterInventory.save_cus = Character::getInstance().inventory.cus;
	pContents->save_character.save_characterInventory.save_max_size = Character::getInstance().inventory.max_size;
	pContents->save_character.save_characterInventory.save_maxsize = Character::getInstance().inventory.maxsize;
	memset(pContents->save_character.save_characterInventory.save_items, 0,  CAPACITY_OF_STORAGE_IN_INVENTORY * sizeof(Item));
	for (int i = 0, len = Character::getInstance().inventory.storage.size(); i < len; ++i)
	{
		pContents->save_character.save_characterInventory.save_items[i] = Character::getInstance().inventory.storage[i];
	}

	/*** 暂时注释掉 */

	////save_shop
	//pContents->save_shop.save_shopInventory.save_cus= Shop::shopgoods->cus;
	//pContents->save_shop.save_shopInventory.save_max_size= Shop::shopgoods->max_size;
	//pContents->save_shop.save_shopInventory.save_maxsize= Shop::shopgoods->maxsize;
	//memset(pContents->save_shop.save_shopInventory.save_items, 0, CAPACITY_OF_STORAGE_IN_INVENTORY * sizeof(Item));
	//for (int i = 0, len = Shop::shopgoods->storage.size(); i < len; ++i)
	//{
	//	pContents->save_shop.save_shopInventory.save_items[i] = Shop::shopgoods->storage[i];
	//}

	//save_time
	/*pContents->save_time.hour = GameTime::getInstance()->hour;
	pContents->save_time.minute = GameTime::getInstance()->minute;
	pContents->save_time.running = GameTime::getInstance()->running;
	pContents->save_time.timeSpeed = GameTime::getInstance()->timeSpeed;*/
}

bool Archive::SaveGame(const char* fileName)
{
	CopyToContents();

	FILE* pFile = fopen(fileName, "wb");//以写二进制方式打开文件
	if (pFile == NULL)
	{
		return false;
	}
	fwrite((void*)pContents, sizeof(Contents), 1, pFile);
	fclose(pFile);
	return true;
}

void Archive::InitFromContents()
{
	//init from save_character
	Character::getInstance().tool = pContents->save_character.save_tool;
	Character::getInstance().speed = pContents->save_character.save_speed;
	Character::getInstance().hunger = pContents->save_character.save_hunger;
	Character::getInstance().water = pContents->save_character.save_water;
	Character::getInstance().money = pContents->save_character.save_money;
	Character::getInstance().inventory.cus = pContents->save_character.save_characterInventory.save_cus;
	Character::getInstance().inventory.max_size = pContents->save_character.save_characterInventory.save_max_size;
	Character::getInstance().inventory.maxsize = pContents->save_character.save_characterInventory.save_maxsize;
	for (int i = 0; i < CAPACITY_OF_STORAGE_IN_INVENTORY; ++i)
	{
		Character::getInstance().inventory.storage[i] = pContents->save_character.save_characterInventory.save_items[i];
	}

	//init from save_shop
	/*Shop::shopgoods->cus = pContents->save_shop.save_shopInventory.save_cus;
	Shop::shopgoods->max_size = pContents->save_shop.save_shopInventory.save_max_size;
	Shop::shopgoods->maxsize = pContents->save_shop.save_shopInventory.save_maxsize;
	for (int i = 0; i < CAPACITY_OF_STORAGE_IN_INVENTORY; ++i)
	{
		Shop::shopgoods->storage[i] = pContents->save_shop.save_shopInventory.save_items[i];
	}*/

	//init from save_time
	/*GameTime::getInstance()->hour = pContents->save_time.hour;
	GameTime::getInstance()->minute = pContents->save_time.minute;
	GameTime::getInstance()->running = pContents->save_time.running;
	GameTime::getInstance()->timeSpeed = pContents->save_time.timeSpeed;*/
}

bool  Archive::ReadFile(const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb");//以读二进制方式打开文件
	if (pFile == NULL)
	{
		return false;
	}
	fread((void*)pContents, sizeof(Contents), 1, pFile);
	fclose(pFile);

	InitFromContents();

	return true;
}