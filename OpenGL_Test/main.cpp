#include <GL/glfw.h>
#include "btBulletDynamicsCommon.h"

#include "colladaloader.h"

#include <stdlib.h>
#include <iostream>

#include <QString>
#include <QFile>

int main( void )
{
    ColladaLoader* cl = new ColladaLoader("c:/Users/Joel/Desktop/cube.dae");
    delete cl;

    int running = GL_TRUE;
    // Initialize GLFW
    if( !glfwInit() )
    {
        exit( EXIT_FAILURE );
    }

    int nummodes;
    GLFWvidmode list[ 200 ];
    nummodes = glfwGetVideoModes( list, 200 );

    // Open an OpenGL window
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if( !glfwOpenWindow( 500, 500, 0,0,0,0,0,0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    glfwSetWindowTitle("My Awesome Window\0");


    /*
    int* major = 0;
    int* minor = 0;
    int* rev = 0;

    glfwGetGLVersion( major, minor, rev );

    QFile f("gl_version.txt");
    f.open(QIODevice::ReadWrite);
    f.write((QString().setNum(*major) + "." + QString().setNum(*minor) + "." + QString().setNum(*rev)).toAscii());
    f.waitForBytesWritten(1000);
    f.close();

    */

    QFile f2("gl_version2.txt");
    f2.open(QIODevice::ReadWrite);
    f2.write(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    f2.waitForBytesWritten(1000);
    f2.close();

    glClearColor(0,0,0,0);
    //glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    double phase = 0.0;

    // Main loop
    while( running )
    {
        phase += 0.01;

        glViewport(0, 0, 500, 500);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1, 1, -1, 1, 1.5, 100);
        glMatrixMode(GL_MODELVIEW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        gluLookAt(10 + sin(phase)*10, 10 + cos(phase) * 10, 10, 0, 0, 0, 0, 1, 0);
        glBegin(GL_QUADS);

        //face in xy plane
        glColor3f(0.82, 0.41, 0.12);
        glVertex3f(0, 0, 0);
        glVertex3f(5, 0, 0);
        glVertex3f(5, 5, 0);
        glVertex3f(0, 5, 0);

        //face in yz plane
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 5);
        glVertex3f(0, 5, 0);
        glVertex3f(0, 5, 5);

        //face in zx plance
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 5);
        glVertex3f(5, 0, 5);
        glVertex3f(5, 0, 0);

        //|| to xy plane.
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 5);
        glVertex3f(5, 0, 5);
        glVertex3f(5, 5, 5);
        glVertex3f(0, 5, 5);

        //|| to yz plane
        glColor3f(0.73, 0.58, 0.58);
        glVertex3f(0, 0, 5 );
        glVertex3f(5, 0, 5);
        glVertex3f(5, 5, 5);
        glVertex3f(0, 5, 5);

        //|| to zx plane
        glVertex3f(0.58, 0, 0.82);
        glVertex3f(0, 5, 0);
        glVertex3f(0, 5, 5);
        glVertex3f(5, 5, 5);
        glVertex3f(5, 5, 0);
        glEnd();
        glFlush();

        // Swap front and back rendering buffers
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
        glfwGetWindowParam( GLFW_OPENED );

        glfwSleep(0.01);
    }
    // Close window and terminate GLFW
    glfwTerminate();
    // Exit program
    exit( EXIT_SUCCESS );
}
