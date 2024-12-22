#include "Skills.h"

void Skills::cultivation_skill_rises(float skill)
{
	if (cultivation + skill >= 1)
	{
		cultivation = 1;
	}
	else
		cultivation += skill;
}
void Skills::breeding_skill_rises(float skill) 
{

	if (breeding + skill >= 1)
	{
		breeding = 1;
	}
	else
		breeding += skill;
}
void Skills::slaughter_skill_rises(float skill)
{

	if (slaughter + skill >= 1)
	{
		slaughter = 1;
	}
	else
		slaughter += skill;
}