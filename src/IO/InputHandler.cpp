/*
 * InputHandler.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: chaorel
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
    // TODO Auto-generated constructor stub
    for (int i = 0; i < 3; ++i) {
        m_mouseButtonStates.push_back(false);
    }

}

InputHandler::~InputHandler() {
    // TODO Auto-generated destructor stub
}

void InputHandler::update() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Demo::Instance()->quit();
            break;
            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(event);
            break;
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(event);
            break;
            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(event);
            break;
            case SDL_MOUSEMOTION:
                onMouseMove(event);
            break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
            break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
            break;
            case SDL_KEYDOWN:
                onKeyDown();
            break;
            case SDL_KEYUP:
                onKeyUp();
            break;
            default:
            break;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[MOUSE_LEFT] = true;
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MOUSE_MIDDLE] = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[MOUSE_RIGHT] = true;
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[MOUSE_LEFT] = false;
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MOUSE_MIDDLE] = false;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[MOUSE_RIGHT] = false;
        }
    }

    if (event.type == SDL_MOUSEMOTION) {
        m_mousePosition.x = event.motion.x;
        m_mousePosition.y = event.motion.y;
    }

}
