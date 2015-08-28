/*
 * myVideo.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: chaoren
 */

#include "myVideo.h"

myVideo::myVideo ( ) :
_name("my window"),
_width(1024), _height(768),
_startX(100), _startY(100),
_antialiasingX(4),
_currentWindow(NULL)
{
    fwInit();
    ewInit();
}

myVideo::~myVideo ( ) {
    // TODO Auto-generated destructor stub
}

myVideo& myVideo::getInstance() {
    static myVideo _theOne;
    return _theOne;
}

void myVideo::fwInit( ) {
    if ( !glfwInit() ) {
        std::fprintf ( stderr, "Failed to initialize GLFW.\n" );
        exit ( EXIT_FAILURE );
    }

    glfwWindowHint ( GLFW_SAMPLES, _antialiasingX ); // 4x antialiasing
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 ); // We want OpenGL 3.3
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 );
//    To make MacOS happy; should not be needed
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); //We don't want the old OpenGL

    // Open a window and create its OpenGL context
//    GLFWwindow* window; // (In the accompanying source code, this variable is global)
    _currentWindow = glfwCreateWindow ( _width, _height, _name, NULL, NULL );
    if ( _currentWindow == NULL ) {
        fprintf ( stderr, "Failed to open GLFW window. \n "
                "If you have an Intel GPU, they are not 3.3 compatible. "
                "Try the 2.1 version of the tutorials.\n" );
        glfwTerminate ( );
        exit ( EXIT_FAILURE );
    }
}

void myVideo::ewInit ( ) {
    glfwMakeContextCurrent (_currentWindow); // Initialize GLEW
    glewExperimental = true; // Needed in core profile

    if ( glewInit ( ) != GLEW_OK ) {
        fprintf ( stderr, "Failed to initialize GLEW\n" );
        exit ( EXIT_FAILURE );
    }
}
