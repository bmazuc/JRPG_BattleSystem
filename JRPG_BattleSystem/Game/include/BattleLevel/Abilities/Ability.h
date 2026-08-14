#ifndef __ABILITY_H_INCLUDED__
#define __ABILITY_H_INCLUDED__

#include <string>

class Character;

class Ability
{
public:
	std::string GetName() const { return name; }

	virtual bool CanExecuteAbility() const { return CanPayCost(); }
	bool CanPayCost() const;
	void PayCost();

	virtual bool Execute() = 0;

	void SetOwner(Character* inOwner) { owner = inOwner; }

	unsigned int GetManaCost() const { return manaCost; }

protected:
	std::string name;
	Character* owner;

	unsigned int manaCost = 0;
};

#endif // __ABILITY_H_INCLUDED__