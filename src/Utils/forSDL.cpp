/*
 * forSDL.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: chaoren
 */

#include "forSDL.h"

void sdl_printError(const char * msg) {
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void sdl_checkError(int line = -1) {
#ifndef NDEBUG
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
    }
#endif
}
