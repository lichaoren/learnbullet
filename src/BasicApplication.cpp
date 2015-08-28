/*
 * BasicApplication.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: chao
 */

#include "BasicApplication.h"

BasicApplication* BasicApplication::Instance() {
    if (NULL == s_pInstance)
        s_pInstance = new SDLDemoApplication();
    return s_pInstance;
}

void BasicApplication::mouseFunc(int button, int state, int x, int y) {
    if (state == 0) {
        m_mouseButtons |= 1 << button;
    } else {
        m_mouseButtons = 0;
    }

    m_mouseOldX = x;
    m_mouseOldY = y;

    btVector3 rayTo = getRayTo(x, y);

    switch (button) {
        case 2: {
            if (state == 0) {

                shootBox(rayTo);
            }
            break;
        }
            ;
        case 1: {

            if (state == 0) {

#if 0
                //apply an impulse
                if (m_dynamicsWorld)
                {
                    btCollisionWorld::ClosestRayResultCallback rayCallback(m_cameraPosition,rayTo);
                    m_dynamicsWorld->rayTest(m_cameraPosition,rayTo,rayCallback);
                    if (rayCallback.hasHit())
                    {

                        btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);
                        if (body)
                        {
                            body->setActivationState(ACTIVE_TAG);
                            btVector3 impulse = rayTo;
                            impulse.normalize();
                            float impulseStrength = 10.f;
                            impulse *= impulseStrength;
                            btVector3 relPos = rayCallback.m_hitPointWorld - body->getCenterOfMassPosition();
                            body->applyImpulse(impulse,relPos);
                        }
                    }
                }
#endif

            } else {

            }
            break;
        }
        case 0: {
            if (state == 0) {

                //add a point to point constraint for picking
                if (m_dynamicsWorld) {

                    btVector3 rayFrom;
                    if (m_camera.projectionMode()) {
                        rayFrom = rayTo;
                        rayFrom.setZ(-100.f);
                    } else {
                        rayFrom = m_camera.getLocation();
                    }

                    btCollisionWorld::ClosestRayResultCallback rayCallback(
                            rayFrom, rayTo);
                    m_dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
                    if (rayCallback.hasHit()) {

                        btVector3 pickPos = rayCallback.m_hitPointWorld;

                        pickObject(pickPos, rayCallback.m_collisionObject);

                        gOldPickingPos = rayTo;

                        gOldPickingDist = (pickPos - rayFrom).length();
                    }
                }

            } else {
                removePickingConstraint();
            }

            break;

        }
        default: {
        }
    }

}

void BasicApplication::mouseMotionFunc(int x, int y) {
    if (m_pickConstraint) {
        if (m_pickConstraint->getConstraintType() == D6_CONSTRAINT_TYPE) {
            btGeneric6DofConstraint* pickCon =
                    static_cast<btGeneric6DofConstraint*>(m_pickConstraint);
            if (pickCon) {
                // keep it at the same picking distance
                btVector3 newRayto = m_camera.ray(x, y);
                btVector3 rayFrom;
                btVector3 oldPivotInB = pickCon->getFrameOffsetA().getOrigin();

                btVector3 newPivotB;
                if (m_camera.projectionMode() == ORTHO) {
                    newPivotB = oldPivotInB;
                    newPivotB.setX(newRayto.getX());
                    newPivotB.setY(newRayto.getY());
                } else {
                    rayFrom = m_camera.getLocation();
                    btVector3 dir = newRayto - rayFrom;
                    dir.normalize();
                    dir *= gOldPickingDist;

                    newPivotB = rayFrom + dir;
                }
                pickCon->getFrameOffsetA().setOrigin(newPivotB);
            }
        } else {
            btPoint2PointConstraint* pickCon =
                    static_cast<btPoint2PointConstraint*>(m_pickConstraint);
            if (pickCon) {
                //keep it at the same picking distance

                btVector3 newRayTo = getRayTo(x, y);
                btVector3 rayFrom;
                btVector3 oldPivotInB = pickCon->getPivotInB();
                btVector3 newPivotB;
                if (m_camera.projectionMode() == ORTHO) {
                    newPivotB = oldPivotInB;
                    newPivotB.setX(newRayTo.getX());
                    newPivotB.setY(newRayTo.getY());
                } else {
                    rayFrom = m_camera.getLocation();
                    btVector3 dir = newRayTo - rayFrom;
                    dir.normalize();
                    dir *= gOldPickingDist;

                    newPivotB = rayFrom + dir;
                }
                pickCon->setPivotB(newPivotB);
            }
        }
    }
    float dx, dy;
    dx = btScalar(x) - m_mouseOldX;
    dy = btScalar(y) - m_mouseOldY;

    m_mouseOldX = x;
    m_mouseOldY = y;
    m_camera.update();
}

void BasicApplication::removePickingConstraint() {
    if (m_pickConstraint && m_dynamicsWorld) {
        m_dynamicsWorld->removeConstraint(m_pickConstraint);
        delete m_pickConstraint;
        //printf("removed constraint %i",gPickingConstraintId);
        m_pickConstraint = 0;
        pickedBody->forceActivationState((int) ACTIVE_TAG);
        pickedBody->setDeactivationTime(0.f);
        pickedBody = 0;
    }
}

virtual void BasicApplication::pickObject(const btVector3& pickPos,
                                          const btCollisionObject* hitObj) {

    btRigidBody* body = (btRigidBody*) btRigidBody::upcast(hitObj);
    if (body) {
        //other exclusions?
        if (!(body->isStaticObject() || body->isKinematicObject())) {
            pickedBody = body;
            pickedBody->setActivationState((int) DISABLE_DEACTIVATION);

            //printf("pickPos=%f,%f,%f\n",pickPos.getX(),pickPos.getY(),pickPos.getZ());

            btVector3 localPivot = body->getCenterOfMassTransform().inverse()
                    * pickPos;

            if ((m_modifierKeys & BT_ACTIVE_SHIFT) != 0) {
                btTransform tr;
                tr.setIdentity();
                tr.setOrigin(localPivot);
                btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(
                        *body, tr, false);
                dof6->setLinearLowerLimit(btVector3(0, 0, 0));
                dof6->setLinearUpperLimit(btVector3(0, 0, 0));
                dof6->setAngularLowerLimit(btVector3(0, 0, 0));
                dof6->setAngularUpperLimit(btVector3(0, 0, 0));

                m_dynamicsWorld->addConstraint(dof6, true);
                m_pickConstraint = dof6;

                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 0);
                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 1);
                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 2);
                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 3);
                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 4);
                dof6->setParam(BT_CONSTRAINT_STOP_CFM, 0.8, 5);

                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 0);
                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 1);
                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 2);
                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 3);
                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 4);
                dof6->setParam(BT_CONSTRAINT_STOP_ERP, 0.1, 5);
            } else {
                btPoint2PointConstraint* p2p = new btPoint2PointConstraint(
                        *body, localPivot);
                m_dynamicsWorld->addConstraint(p2p, true);
                m_pickConstraint = p2p;
                p2p->m_setting.m_impulseClamp = mousePickClamping;
                //very weak constraint for picking
                p2p->m_setting.m_tau = 0.001f;
                /*
                 p2p->setParam(BT_CONSTRAINT_CFM,0.8,0);
                 p2p->setParam(BT_CONSTRAINT_CFM,0.8,1);
                 p2p->setParam(BT_CONSTRAINT_CFM,0.8,2);
                 p2p->setParam(BT_CONSTRAINT_ERP,0.1,0);
                 p2p->setParam(BT_CONSTRAINT_ERP,0.1,1);
                 p2p->setParam(BT_CONSTRAINT_ERP,0.1,2);
                 */

            }

            //save mouse position for dragging

        }
    }

}

BasicApplication::BasicApplication() {
    // TODO Auto-generated constructor stub

}

BasicApplication::~BasicApplication() {
    // TODO Auto-generated destructor stub
}

void BasicApplication::moveAndDisplay() {
    if (!m_idle)
        clientMoveAndDisplay();
    else
        displayCallback();
}

void BasicApplication::displayCallback() {
}

