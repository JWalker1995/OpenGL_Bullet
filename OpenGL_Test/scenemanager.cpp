#include "scenemanager.h"

#include "btBulletDynamicsCommon.h"

#define GLEW_STATIC
#include "3rd_party/glew.c"
#include <GL/glfw.h>

#include <stdlib.h>
#include <iostream>


SceneManager::SceneManager()
{
    // Initialize GLFW
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    /*
    int nummodes;
    GLFWvidmode list[ 200 ];
    nummodes = glfwGetVideoModes( list, 200 );
    */
/*
    // Open an OpenGL window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
*/
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow(500, 500, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowTitle("My Awesome Window\0");

    // Initialize glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        //fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(err);
    }

    //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Main loop
    while (true)
    {
        glfwSetTime(0.0);// Sets time to zero, so we know later how much time the frame took

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers();

        // If ESC key is pressed or window is closed, break out of loop
        if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {break;}

        glfwGetTime();
        glfwSleep(0.1);
    }

    glfwCloseWindow();
    glfwTerminate();
}

SceneManager::~SceneManager()
{
}
