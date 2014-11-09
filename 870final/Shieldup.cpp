#include "Shieldup.h"

const int FPS = 60;
const int DELAY_TIME = 1000.f / FPS;

const glm::vec3 axisX(1,0,0);
const glm::vec3 axisY(0,1,0);
const glm::vec3 axisZ(0,0,1);

int main ( ) {
    GLint err;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
        sdl_printError("Initializing SDL failed");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//    Turn on double buffering with a 24bit Z buffer
//    You may need to change this to 16 or 32 for your system
//    not working on lab machines if set to 32
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Camera cam1;
    SDL_Window *window = SDL_CreateWindow( "My Game Window",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           cam1.getWidth(), cam1.getHeight(),
                                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    if (!window)
        sdl_printError("Unable to create window");
    sdl_checkError(__LINE__);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    sdl_checkError(__LINE__);


    const unsigned char *glVersion = glGetString(GL_VERSION);
    if (glVersion == NULL) {
        std::printf("Unable to get OpenGL Version.\n");
        exit(EXIT_FAILURE);
    }

//    This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    SDL_GL_MakeCurrent(window, glContext);

//    the glewExperimental global switch can be turned on by setting it to GL_TRUE before
//    calling glewInit(), which ensures that all extensions with valid entry points will be exposed.
    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (glew_status != 0) {
        std::fprintf(stderr, "Error: %s.\n", glewGetErrorString(glew_status) );
        return(EXIT_FAILURE);
    }
    err = glGetError();
    if (0 != err) std::printf("glError: %d.\n", err);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST|GL_DOUBLEBUFFER);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    if (!loadOBJ("./Asset/Model/cube.obj", vertices, uvs, normals) ) {
        std::fprintf(stderr, "Loading OBJ file failed.\n");
        return(EXIT_FAILURE);
    }

    std::vector<std::string> vtxShaderList;
    vtxShaderList.push_back( readToString("vtx.glsl", NULL) );
    std::vector<std::string> frgShaderList;
    frgShaderList.push_back( readToString("frg.glsl", NULL) );

    GLuint programID;
    initializeProgram(programID, vtxShaderList, frgShaderList);

    // Get a handle for our "MVP" uniform.
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    GLuint textureBufferID = loadTexture("./Asset/Texture/uvmap.jpg");
    GLuint textureID = glGetUniformLocation(programID, "txSampler");


//    Generate 1 vertex array ID for use
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    // set a handle for light position uniform
    glUseProgram(programID);
    GLuint lightID = glGetUniformLocation(programID, "lightPos_w");


    // Initial position : on +Z
    cam1.setLocation(0, 5, 5);
    cam1.setTarget(0, 0, 0);
    cam1.setUp(axisY);
    cam1.setRight(axisX);
    cam1.refine();
    glm::vec3 lightPos = glm::vec3(0, 10, 0);

    glm::mat4 M = glm::mat4 (1.0f);

    float speed = 1.0f; // 3 units / second
    float mouseSpeed = 0.0005f;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    Uint32 startTime = SDL_GetTicks(), frameTime = 0, delta = 0;
    int mouseX, mouseY;
    bool gameLoop = true;
    while (gameLoop) {
        delta = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();
        SDL_Event e;
        const Uint8 * m_keystates = (Uint8 *) SDL_GetKeyboardState(NULL);

        mouseX = mouseY = 0;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                gameLoop = false;

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    gameLoop = false;
                if (e.key.keysym.sym == SDLK_a){
                    printf("%f %f %f\n", cam1.getTarget()[0], cam1.getTarget()[1], cam1.getTarget()[2]);
                    cam1.rotate(10);
                    printf("%f %f %f\n", cam1.getTarget()[0], cam1.getTarget()[1], cam1.getTarget()[2]);
                    printf("pressed a\n");
                }
                if (e.key.keysym.sym == SDLK_d){
                    printf("%f %f %f\n", cam1.getTarget()[0], cam1.getTarget()[1], cam1.getTarget()[2]);
                    cam1.rotate(-10);
                    printf("%f %f %f\n", cam1.getTarget()[0], cam1.getTarget()[1], cam1.getTarget()[2]);
                    printf("pressed a\n");
                }
                if (e.key.keysym.sym == SDLK_w){
                    cam1.setLocation(cam1.getLocation()+0.1f*cam1.getAim());
                }
                if (e.key.keysym.sym == SDLK_s){
                    cam1.setLocation(cam1.getLocation()-0.1f*cam1.getAim());
                }
            }



            if (e.type == SDL_MOUSEMOTION) {
                mouseX = e.motion.yrel; }
        }

        glm::mat4 MVP = cam1.getProjectMatrix() * cam1.getViewMatrix() * M; // Remember, matrix multiplication is the other way around
//        printf("%d", w_pressed);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        // send out transformation to the currently bound shader,
        // in MVP uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, glm::value_ptr(cam1.getViewMatrix()));
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, glm::value_ptr(cam1.getProjectMatrix()));


        glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureBufferID);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(textureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        SDL_GL_SwapWindow(window);
//        frameTime = SDL_GetTicks() - startTime;
//        if (frameTime < (int)DELAY_TIME)
//            SDL_Delay(int(DELAY_TIME) - frameTime);
        startTime = SDL_GetTicks();
    }

//    glUseProgram(0);
//    glDetachShader(programID);
//    glDeleteProgram();
//    glDeleteShader();
//    glDeleteBuffers();
//    glDeleteVertexArrays();
//    free(vertexresource);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;


}


