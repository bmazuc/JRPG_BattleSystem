#ifndef __ABILITY_H_INCLUDED__
#define __ABILITY_H_INCLUDED__

#include <string>

class Actor;

class Ability
{
public:
	std::string GetName() const { return name; }

	virtual bool CanExecuteAbility() { return true; }

	virtual bool Execute() = 0;

	void SetOwner(Actor* inOwner) { owner = inOwner; }

protected:
	std::string name;
	Actor* owner;
};

#endif // __ABILITY_H_INCLUDED__