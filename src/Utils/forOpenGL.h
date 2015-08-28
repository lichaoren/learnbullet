/*
 * forOpenGL.h
 *
 * This file contains ultilities for OpenGL use.
 *
 *  Created on: Aug 26, 2014
 *      Author: chaoren
  */

#ifndef FOROPENGL_H_
#define FOROPENGL_H_

#define GLM_FORCE_RADIANS

#include "../IO/File.h"
#include "../IO/OIIOFiles.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <vector>
#include <cstring>
#include <iterator>
#include <algorithm>

enum {DELTE_AFTERLOAF, NOT_DELETE_AFTERLOAD};

GLuint loadTexture(const char * imagepath, const int flag = NOT_DELETE_AFTERLOAD);

GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
GLuint createProgram(const std::vector<GLuint> &shaderList);

void initializeProgram(GLuint &theProgram,
                       std::vector<std::string> const &VtxShaderList,
                       std::vector<std::string> const &FrgShaderList);


#endif
