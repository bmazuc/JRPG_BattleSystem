#ifndef __ABILITY_H_INCLUDED__
#define __ABILITY_H_INCLUDED__

#include <string>

class Character;

/**
 * Base class for all character abilities.
 *
 * Handles common ability functionality such as:
 * - ability ownership
 * - mana cost management
 * - execution validation
 *
 * Concrete abilities implement their gameplay-specific behavior
 * through Execute().
 */
class Ability
{
public:
	std::string GetName() const { return name; }

	/**
	 * Checks whether the ability can currently be executed.
	 * By default, an ability can be executed when its mana cost can be paid.
	 */ 
	virtual bool CanExecuteAbility() const { return CanPayCost(); }
	/**
	 * Checks whether the owner has enough mana to pay the ability cost.
	 */
	bool CanPayCost() const;
	/**
	 * Deducts the ability's mana cost from its owner.
	 */
	void PayCost();

	/**
	 * Executes the ability.
	 * @return True if the ability was successfully executed, false otherwise.
	 */
	virtual bool Execute() = 0;

	void SetOwner(Character* inOwner) { owner = inOwner; }

	unsigned int GetManaCost() const { return manaCost; }

protected:
	// Display name of the ability.
	std::string name;
	// Character that owns the ability.
	Character* owner;
	//  Mana required to use the ability.
	unsigned int manaCost = 0;
};

#endif // __ABILITY_H_INCLUDED__