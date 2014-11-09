/*
 * myManager.h
 *
 *  Created on: Aug 23, 2014
 *      Author: chaoren
 */

#ifndef MYMANAGER_H_
#define MYMANAGER_H_

class myManager {
public:
    myManager ( );
    ~myManager ( );
    static myManager& getInstance();


private:

    myManager(const myManager&);
    myManager& operator=(const myManager&);
};

#endif /* MYMANAGER_H_ */
