/*
 * BasicApplication.h
 *
 *  Created on: Oct 6, 2014
 *      Author: chao
 */

#ifndef BASICAPPLICATION_H_
#define BASICAPPLICATION_H_

#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btQuickprof.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "Utils/Camera.h"
#include "IO/InputHandler.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

class btCollisionShape;
class btDynamicsWorld;
class btRigidBody;
class btTypedConstraint;

class BasicApplication
{
#ifdef USE_BT_CLOCK
    btClock m_clock;
#endif // USE_BT_CLOCK

    btDynamicsWorld * m_dynamicsWorld;

    btTypedConstraint * m_pickConstraint;
    int gPickingConstraintId = 0;
    btVector3 gOldPickingPos;
    btVector3 gHitPos(-1, -1, -1);
    btScalar gOldPickingDist  = 0.f;
    btRigidBody* pickedBody = 0;//for deactivation state
    virtual void removePickingConstraint();
    virtual void pickObject(const btVector3& pickPos,
                            const class btCollisionObject* hitObj);

    btCollisionShape * m_shootBoxShape;

    float   m_ShootBoxInitialSpeed;

    bool    m_stepping;
    bool m_singleStep;
    bool m_idle;
    int m_lastKey;

    Camera m_camera;
    InputHandler m_input;

    void render(int pass);

    GL_ShapeDrawer* m_shapeDrawer;
    bool m_enableshadows;
    btVector3 m_sunDirection;
    btScalar m_defaultContactProcessingThreshold;

public:
    BasicApplication();
    virtual ~BasicApplication();

    btDynamicsWorld* getDynamicsWorld() {
        return m_dynamicsWorld;
    }

    virtual void initPhysics() = 0;
    virtual void setDrawCluster(bool drawClusters) {}
    void overrideGLShapeDrawer (GL_ShapeDrawer* shapeDrawer);
    bool    setTexturing(bool enable) { return(m_shapeDrawer->enableTexture(enable)); }
    bool    setShadows(bool enable) { bool p=m_enableshadows;m_enableshadows=enable;return(p); }
    bool    getTexturing() const
    {
        return m_shapeDrawer->hasTextureEnabled();
    }
    bool    getShadows() const
    {
        return m_enableshadows;
    }

    int m_debug;
    void setDebug(int mode) {
        m_debug = mode;
    }
    int getDebug() const {
        return m_debug;
    }

    virtual void myinit();

    void toggleidle();
    btScalar getDeltaTimeMicroseconds() {
#ifdef USE_BT_CLOCK
        btScalar dt = (btScalar) m_clock.getTimeMicroseconds();
        m_clock.reset();
        return dt;
#else
        return btScalar(16666.);
#endif
    }

    BasicApplication* Instance();

    int m_mouseOldX;
    int m_mouseOldY;
    int m_mouseButtons;

    void moveAndDisplay();
    virtual void clientMoveAndDisplay() = 0;

    virtual void clientResetScene();

    virtual void setShootBoxShape ();
    virtual void    shootBox(const btVector3& destination);

    btVector3  getRayTo(int x,int y);

    btRigidBody*    localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);

    // Call backs
    virtual void mouseFunc(int, int, int, int);
    virtual void mouseMotionFunc(int x,int y);
    virtual void displayCallback();
    virtual void renderme();
    virtual void swapBuffers() = 0;

    bool getIdle() const {
        return m_idle;
    }
    void setIdle(bool i) {
        m_idle = i;
    }
    btScalar mousePickClamping = 30.f;

    static BasicApplication* s_pInstance;

};

#endif /* BASICAPPLICATION_H_ */
