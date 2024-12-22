#ifndef ANIMAL_H
#define ANIMAL_H

#include "GameTime.h"
#include <string>
class Animal {
protected:
	int level; //动物等级
	int appetite;//动物饥饿度
public:
	Animal() {
		level = 0;
		appetite = 0;
	}
	bool Can_Feeded_Again = true;
	bool Is_Dead = false;

	virtual bool Killed() = 0;
	virtual void Feeded() = 0;
	int GetAppetite() const {
		return appetite;
	}
	int Get_Level() const {
		return level;
	}
	void Set_Feed_Status() {
		Can_Feeded_Again = true;
	}
};

class Chicken : public Animal {
protected:
	int egg;
public:
	Chicken() {
		appetite = 1;
		egg = 0;
	}
	virtual bool Killed() override {
		if (level == 5) {
			Is_Dead = true;
			return true;
		}
		return false;
	}
	virtual void Feeded() override {
		if (!Is_Dead && Can_Feeded_Again) {
			level += 1;
			if (level > 5)
				level = 5;
			egg += 1;
			Can_Feeded_Again = false;
		}
	}
	bool Get_Egg(int num) {
		egg -= num;
		if (egg < 0) {
			egg = 0;
			return false;
		}
		return true;
	}
	int Egg_Num() const {
		return egg;
	}
};

class Sheep : public Animal {
protected:
	int wool;
public:
	Sheep() {
		appetite = 2;
		wool = 0;
	}
	virtual bool Killed() override {
		if (level == 10) {
			Is_Dead = true;
			return true;
		}
		return false;
	}
	virtual void Feeded() override {
		if (!Is_Dead && Can_Feeded_Again) {
			level += 1;
			if (level > 10)
				level = 10;
			wool += 2;
			Can_Feeded_Again = false;
		}
	}
	bool Get_Wool(int num) {
		wool -= num;
		if (wool < 0) {
			wool = 0;
			return false;
		}
		return true;
	}
	int Wool_Num() const {
		return wool;
	}
};

#endif // ANIMAL_H
