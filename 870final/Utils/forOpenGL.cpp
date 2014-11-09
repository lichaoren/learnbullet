/*
 * forOpenGL.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: chaoren
 */
#include "forOpenGL.h"


GLuint loadTexture(const char * imagepath, const int flag){

    std::vector<unsigned char> image;

    readOIIOImage(imagepath, image);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 512, 512,
                 0, GL_BGR, GL_UNSIGNED_BYTE, (unsigned char*)(&image[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}


void initializeProgram(GLuint &theProgram,
                       std::vector<std::string> const &VtxShaderList,
                       std::vector<std::string> const &FrgShaderList) {
    std::vector<GLuint> shaderList;

    for ( std::vector<std::string>::const_iterator it = VtxShaderList.begin();
          it != VtxShaderList.end();
          ++it) {
        shaderList.push_back(createShader(GL_VERTEX_SHADER, *it));
    }

    for ( std::vector<std::string>::const_iterator it = FrgShaderList.begin();
          it != FrgShaderList.end();
          ++it) {
        shaderList.push_back(createShader(GL_FRAGMENT_SHADER, *it));
    }

    theProgram = createProgram(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

GLuint createShader(GLenum eShaderType, const std::string &strShaderFile)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch(eShaderType)
        {
            case GL_VERTEX_SHADER:   strShaderType = "vertex";   break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        std::fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

GLuint createProgram(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glAttachShader(program, shaderList[iLoop]);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        std::fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);

    return program;
}



