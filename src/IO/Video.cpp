/*
 * Video.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: chaoren
 */

#include "Video.h"

Video::Video() :        _name("Sheildup"), _width(640), _height(480), _window(NULL),
        _context(NULL) {
    initialize();
}

Video::Video(std::string _n,
             unsigned int _w, unsigned int _h) :
        _name(_n), _width(_w), _height(_h), _window(NULL),
        _context(NULL) {
    initialize();
}

Video::~Video() {
    // TODO Auto-generated destructor stub
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
}

void Video::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_printError("Initializing SDL failed");

//    const unsigned char *glVersion = glGetString(GL_VERSION);
//    if (glVersion == NULL) {
//        std::printf("Unable to get OpenGL Version.\n");
//        exit(EXIT_FAILURE);
//    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    _window = SDL_CreateWindow(_name.c_str(),
    SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, _width,
                               _height,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!_window)
        sdl_printError("Unable to create window");
    sdl_checkError(__LINE__);

    _context = SDL_GL_CreateContext(_window);
    sdl_checkError(__LINE__);

    //    This makes our buffer swap synchronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    SDL_GL_MakeCurrent(_window, _context);

    //    the glewExperimental global switch can be turned on by setting it to GL_TRUE before
    //    calling glewInit(), which ensures that all extensions with valid entry points will be exposed.
    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();

    std::printf("glError: %d.\n", glGetError());
    if (glew_status != 0) {
        std::fprintf(stderr, "Error: %s.\n",
                     glewGetErrorString(glew_status));
        exit(EXIT_FAILURE);
    }
}
