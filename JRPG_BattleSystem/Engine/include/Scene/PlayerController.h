#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

class InputManager;

#include <functional>
#include <glm/vec2.hpp>

class PlayerController
{
public:
	void UpdateInputs(const InputManager* inputManager);

	std::function<void()> OnClick;

	glm::vec2 GetMousePosition() const { return mousePos; }

private:
	glm::vec2 mousePos;
};

#endif // __PLAYER_CONTROLLER_H__