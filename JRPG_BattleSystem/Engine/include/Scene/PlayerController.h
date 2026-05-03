#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

class InputManager;

#include "Core/Delegate/Delegate.h"
#include <glm/vec2.hpp>

class PlayerController
{
public:
	~PlayerController();

	void UpdateInputs(const InputManager* inputManager);

	Delegate<void> OnClick;

	glm::vec2 GetMousePosition() const { return mousePos; }

private:
	glm::vec2 mousePos;
};

#endif // __PLAYER_CONTROLLER_H__