/*
 * main.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: chao
 */

#include "SDLDemoApplication.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"

int main(int argc, char** argv) {
    SDLDemoApplication mydemo;
    mydemo.initPhysics();

    mydemo.run(argc, argv);
    printf("run\n");

    return EXIT_SUCCESS;
}


