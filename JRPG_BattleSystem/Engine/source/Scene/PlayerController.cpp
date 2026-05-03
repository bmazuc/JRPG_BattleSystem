#include "Scene/PlayerController.h"
#include "Core/Inputs/InputManager.h"
#include <SDL3/SDL_mouse.h>

PlayerController::~PlayerController()
{
	OnClick.Clear();
}

void PlayerController::UpdateInputs(const InputManager* inputManager)
{
	mousePos = inputManager->GetMousePosition();
	if (inputManager->IsMousePressed(SDL_BUTTON_LEFT))
	{
		OnClick.Call();
	}
}