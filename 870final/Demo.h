/*
 * Demo.h
 *
 *  Created on: Sep 22, 2014
 *      Author: chaorel
 */

#ifndef DEMO_H_
#define DEMO_H_

#ifdef _WINDOWS
#include "Win64DemoApplication.h"
#define PlatformDemoApplication Win64DemoApplication
#else
#include "SDLDemoApplication.h"
#define PlatformDemoApplication SDLDemoApplication
#endif

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

class Demo : public PlatformDemoApplication
{
public:
    Demo();
    virtual ~Demo();

    void initPhysics();
    void cleanPhysics() {}

    virtual void run() {}

    virtual void clientMoveAndDisplay() {}
    virtual void displayCallBack() {}
    virtual void clientReset() {}


};

#endif /* DEMO_H_ */
