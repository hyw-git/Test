#ifndef __SKILLS_H__
#define __SKILLS_H__

class Skills
{
	friend class Archive;
private:
	float cultivation;
	float breeding;
	float slaughter;
public:
	float get_cultivation_skills() { return cultivation; }
	float get_breeding_skills() { return breeding; }
	float get_slaughter_skills() { return skills; }
	void set_cultivation_skill(float skill) { cultivation = skill; }
	void set_breeding_skill(float skill) { breeding = skill; }
	void set_slaughter_skills(float skill) { slaughter = skill; }
	void cultivation_skill_rises(float skill);
	void breeding_skill_rises(float skill);
	void slaughter_skill_rises(float skill);
};