/*
 * File.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: chaoren
 */

#include "File.h"

std::string readToString(const char* fileName, char* dst = NULL) {
    std::string data;
    std::ifstream fileStream(fileName, std::ios::in);
    if ( fileStream.is_open() ) {
        std::string line("");
        while ( getline(fileStream, line) ) {
            data += line + '\n';
        }
        fileStream.close();
    }

    if (dst != NULL)
        strcpy(dst, data.c_str());
    return data;
}


