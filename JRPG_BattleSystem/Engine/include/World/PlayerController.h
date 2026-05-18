#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

class InputManager;

#include "Core/Delegate/Delegate.h"
#include <glm/vec2.hpp>

/**
 * Translates input into gameplay actions.
 * The PlayerController acts as an abstraction layer between:
 * - raw input (InputManager)
 * - gameplay systems (Actors, UI, etc.)
 */
class PlayerController
{
public:
	~PlayerController();

	/**
	 * Updates internal input state from InputManager.
	 */
	void UpdateInputs(const InputManager* inputManager);

	/**
	 * Triggered when the player clicks (mouse or action input).
	 */
	Delegate<void> OnClick;

	/**
	 * Current mouse position in screen space.
	 */
	glm::vec2 GetMousePosition() const { return mousePos; }

private:
	glm::vec2 mousePos;
};

#endif // __PLAYER_CONTROLLER_H__