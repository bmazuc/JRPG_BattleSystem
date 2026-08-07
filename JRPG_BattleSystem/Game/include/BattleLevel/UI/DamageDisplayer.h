#ifndef __DAMAGE_DISPLAYER_H_INCLUDED__
#define __DAMAGE_DISPLAYER_H_INCLUDED__

#include "UI/Text.h"

class DamageDisplayer : public Text
{
public:
	void Display(int damageTaken);

private:
	bool isFading = false;
};

#endif // __DAMAGE_DISPLAYER_H_INCLUDED__