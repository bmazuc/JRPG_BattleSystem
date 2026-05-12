#ifndef __INPUT_MANAGER_H_INCLUDED__
#define __INPUT_MANAGER_H_INCLUDED__

#include <glm/vec2.hpp>

/**
 * Handles window and mouse input state.
 */
class InputManager
{
public:
    /**
     * Polls window events and updates input states.
     */
	void UpdateInputs();

    glm::vec2 GetMousePosition() const { return mousePos; }

    /**
     * Returns true while the mouse button is held down.
     */
    bool IsMouseDown(int button) const;

    /**
     * Returns true only on the frame the mouse button was pressed.
     */
    bool IsMousePressed(int button) const;

    bool IsQuitRequested() const { return isQuitRequested; }
    bool IsWindowResized() const { return isWindowResized; }

    glm::vec2 GetWindowSize() const { return windowSize; }

private:
    glm::vec2 mousePos;

    // Current mouse button states.
    bool mouseDown[3];

    // Mouse buttons pressed during the current frame.
    bool mousePressed[3];

    // Have the application requested shutdown ?
    bool isQuitRequested;

    // Have the window size changed this frame?
    bool isWindowResized;

    glm::vec2 windowSize;
};

#endif // __INPUT_MANAGER_H_INCLUDED__