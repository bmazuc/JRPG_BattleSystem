#include "Core/Inputs/InputManager.h"
#include <SDL3/SDL_events.h>

void InputManager::UpdateInputs()
{
    //reset pressed
    for (int i = 0; i < 3; i++)
    {
        mousePressed[i] = false;
    }

    isQuitRequested = false;
    isWindowResized = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            {
                isQuitRequested = true;
            }
            break;

        case SDL_EVENT_WINDOW_RESIZED:
            {
                isWindowResized = true;
                windowSize = { event.window.data1, event.window.data2 };
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
            {
                mousePos = glm::vec2(event.motion.x, event.motion.y);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                mouseDown[event.button.button - 1] = true;
                mousePressed[event.button.button - 1] = true;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                mouseDown[event.button.button - 1] = false;
            }
            break;
        }
	}
}

bool InputManager::IsMouseDown(int button) const
{
    button -= 1;
    if (button >= 3)
    {
        return false;
    }

    return mouseDown[button];
}

bool InputManager::IsMousePressed(int button) const
{
    button -= 1;
    if (button >= 3)
    {
        return false;
    }

    return mousePressed[button];
}