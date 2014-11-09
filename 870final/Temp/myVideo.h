/*
 * myVideo.h
 *
 *  Created on: Aug 23, 2014
 *      Author: chaoren
 */

#ifndef MYVIDEO_H_
#define MYVIDEO_H_

#include <cstdio>

#include <GL/glew.h> // OpenGL Extension Wrangler, enable the latest OpenGL features, include this before any OpenGL headers

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class myVideo {
public:
    myVideo ( );
    ~myVideo ( );

    static myVideo& getInstance();

    void fwInit();
    void ewInit();

    GLFWwindow* getWindow() {
        return _currentWindow;
    }

private:
    char* _name;
    unsigned int _width, _height;
    unsigned int _startX, _startY;
    unsigned short _antialiasingX;

    GLFWwindow* _currentWindow;


    myVideo(const myVideo&);
    myVideo& operator=(const myVideo&);
};

#endif /* MYVIDEO_H_ */
