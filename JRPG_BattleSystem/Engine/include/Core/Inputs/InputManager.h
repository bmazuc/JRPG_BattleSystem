#ifndef __INPUT_MANAGER_H_INCLUDED__
#define __INPUT_MANAGER_H_INCLUDED__

#include <glm/vec2.hpp>

class InputManager
{
public:
	void UpdateInputs();

    glm::vec2 GetMousePosition() const { return mousePos; }
    bool IsMouseDown(int button) const;
    bool IsMousePressed(int button) const;

    bool IsQuitRequested() const { return isQuitRequested; }
    bool IsWindowResized() const { return isWindowResized; }

    glm::vec2 GetWindowSize() const { return windowSize; }

private:
    glm::vec2 mousePos;
    bool mouseDown[3];
    bool mousePressed[3];

    bool isQuitRequested;
    bool isWindowResized;
    glm::vec2 windowSize;
};

#endif // __INPUT_MANAGER_H_INCLUDED__