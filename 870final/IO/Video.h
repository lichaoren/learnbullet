/*
 * Video.h
 *
 *  Created on: Aug 31, 2014
 *      Author: chaoren
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include "../Utils/forSDL.h"
#include "../Utils/forOpenGL.h"

/* 
 * 
 */
class Video
{
public:
    Video();
    Video(std::string, unsigned int, unsigned int);
    virtual ~Video();

    SDL_Window * getWindow() {
        return _window;
    }

    SDL_GLContext getContext() {
        return _context;
    }

private:
    std::string _name;
    unsigned int _width, _height;
    SDL_Window * _window;
    SDL_GLContext _context;

    void initialize();

    Video(const Video&);
    Video& operator=(const Video&);
};

#endif /* VIDEO_H_ */
