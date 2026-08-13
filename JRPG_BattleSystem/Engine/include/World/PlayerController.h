#ifndef __PLAYER_CONTROLLER_H_INCLUDED__
#define __PLAYER_CONTROLLER_H_INCLUDED__

#include "Core/Delegate/Delegate.h"
#include <glm/vec2.hpp>

class InputManager;

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
	 * Triggered when the player clicks on left button.
	 */
	Delegate<void> OnClick;

	/**
	 * Triggered when the player clicks on right button.
	 */
	Delegate<void> OnRightClick;

	/**
	 * Current mouse position in screen space.
	 */
	glm::vec2 GetMousePosition() const { return mousePos; }

private:
	glm::vec2 mousePos;
};

#endif // __PLAYER_CONTROLLER_H_INCLUDED__