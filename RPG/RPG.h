#ifndef RPG_H
#define RPG_H
#include <string>

class Role
{
private:
	std::string name;
	int HP;
	int MP;
	int LV;

public:
	Role();

	void setName(std::string newName);
	void setHP(int newHP);
	void setMP(int newMP);
	void setLV(int newLV);

	std::string getName();
	int getHP();
	int getMP();
	int getLV();
};

class Enemy
{
private:
	int HP;

public:
	Enemy();

	void setHP(int newHP);
	void setMP(int newMP);
	int getHP();
	int getMP();
};

#endif