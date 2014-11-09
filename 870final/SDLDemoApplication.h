/*
 * SDLDemoApplication.h
 *
 *  Created on: Oct 6, 2014
 *      Author: chao
 */

#ifndef SDLDEMOAPPLICATION_H_
#define SDLDEMOAPPLICATION_H_

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btAlignedObjectArray.h"

class   btCollisionShape;
class   btDynamicsWorld;
class   btRigidBody;
class   btTypedConstraint;

class SDLDemoApplication
{
public:
    SDLDemoApplication();
    virtual ~SDLDemoApplication();

    void init();
    void clean();
    void reset();
    void idle();
    void run(unsigned int, char**) {}

    void initPhysics() {}
    void cleanPhysics();

    btDynamicsWorld* getDynamicsWorld() {
        return m_dynamicsWorld;
    }


private:
    btDynamicsWorld* m_dynamicsWorld;
    btTypedConstraint* m_pickConstraint;
    btCollisionShape* m_shootBoxShape;

    void removePickingConstraint() {}
    void pickObject(const btVector3& pickPos, const class btCollisionObject* hitObj) {}

};

#endif /* SDLDEMOAPPLICATION_H_ */
