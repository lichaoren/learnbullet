/*
 * InputHandler.h
 *
 *  Created on: Sep 9, 2014
 *      Author: chaorel
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "LinearMath/btVector3.h"
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

#include <vector>

enum MOUSE_BUTTONS {MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_RIGHT};

class InputHandler
{
public:
    static InputHandler * Instance() {
        if(NULL == s_pInstance)
                s_pInstance = new InputHandler();
        return s_pInstance;
    }

    void update();
    void clean();

    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

    bool getMouseButtonState(MOUSE_BUTTONS buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }
    const glm::ivec2& getMousePosition() {
        return m_mousePosition;
    }

private:
    std::vector<bool> m_mouseButtonStates;
    glm::ivec2 m_mousePosition;

    InputHandler();
    ~InputHandler ();
    static InputHandler * s_pInstance;
};

typedef InputHandler TheInputHandler;

#endif /* INPUTHANDLER_H_ */
