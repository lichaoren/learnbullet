cmake_minimum_required(VERSION 2.8.4)
project(projSDL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Dynamics/Solver.cpp
    Dynamics/Solver.h
    IO/Controls.cpp
    IO/Controls.h
    IO/File.cpp
    IO/File.h
    IO/Image.cpp
    IO/Image.h
    IO/InputHandler.cpp
    IO/InputHandler.h
    IO/OBJFile.cpp
    IO/OBJFile.h
    IO/OIIOFiles.cpp
    IO/OIIOFiles.h
    IO/Video.cpp
    IO/Video.h
    Temp/Camera1.C
    Temp/Camera1.h
    Temp/CmdLineFind.h
    Temp/gamedata.cpp
    Temp/gamedata.h
    Temp/LinearAlgebra.C
    Temp/LinearAlgebra.h
    Temp/main.cpp
    Temp/myVideo.cpp
    Temp/myVideo.h
    Temp/OBJFile.C
    Temp/OBJFile.h
    Temp/OIIOFiles.C
    Temp/OIIOFiles.h
    Temp/ProgressMeter.h
    Temp/Shieldup.cpp
    Temp/Shieldup.h
    Temp/Utility.C
    Temp/Utility.h
    Temp/Vector.C
    Temp/Vector.h
    Utils/Camera.cpp
    Utils/Camera.h
    Utils/CommandLineArguments.h
    Utils/forGLM.h
    Utils/forOpenGL.cpp
    Utils/forOpenGL.h
    Utils/forSDL.cpp
    Utils/forSDL.h
    Utils/Miscelaneous.h
    Utils/tinyxml2.cpp
    Utils/tinyxml2.h
    BasicApplication.cpp
    BasicApplication.h
    Demo.cpp
    Demo.h
    frg.glsl
    main.cpp
    manager.cpp
    manager.h
    SDLDemoApplication.cpp
    SDLDemoApplication.h
    vtx.glsl)

add_executable(projSDL ${SOURCE_FILES})