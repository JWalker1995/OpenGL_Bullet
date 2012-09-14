#include "scenemanager.h"
#include "colladaloader.h"

#include <stdlib.h>
#include <iostream>

#include <QString>
#include <QFile>

int main( void )
{
    SceneManager scene;// Initiates opengl instance

    ColladaLoader cl = ColladaLoader("c:/dae_samples/cube.dae");

    // Main loop
/*
    while( running )
    {
    // OpenGL rendering goes here...
    glClear( GL_COLOR_BUFFER_BIT );
    // Swap front and back rendering buffers
    glfwSwapBuffers();
    // Check if ESC key was pressed or window was closed
    running = !glfwGetKey( GLFW_KEY_ESC ) &&
    glfwGetWindowParam( GLFW_OPENED );
    }
*/
}
