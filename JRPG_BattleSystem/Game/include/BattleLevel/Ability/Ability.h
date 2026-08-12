#ifndef __ABILITY_H_INCLUDED__
#define __ABILITY_H_INCLUDED__

#include <string>

class Ability
{
public:
	std::string GetName() const { return name; }

	virtual void Execute() = 0;

protected:
	std::string name;
};

#endif // __ABILITY_H_INCLUDED__