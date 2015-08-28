/*
 * Demo.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: chaorel
 */

#include "Demo.h"
#include "btBulletDynamicsCommon.h"

#include <cstdio>
#include "LinearMath/btAabbUtil2.h"


Demo::Demo () {
    // TODO Auto-generated constructor stub
}

Demo::~Demo () {
    // TODO Auto-generated destructor stub
	cleanPhysics();
}

