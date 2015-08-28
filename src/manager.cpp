/*
 * myManager.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: chaoren
 */

#include "manager.h"

myManager::myManager ( )
{
    // TODO Auto-generated constructor stub

}

myManager::~myManager ( ) {
    // TODO Auto-generated destructor stub
}

myManager& myManager::getInstance() {
    static myManager _theOne;
    return _theOne;
}

