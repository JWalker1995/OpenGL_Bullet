#include <GL/glfw.h>
#include <stdlib.h>
#include <iostream>

#include <QString>
#include <QFile>

int main( void )
{
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

    /*
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };


    // This will identify our vertex buffer
    GLuint vertexbuffer;

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
*/
    // Main loop
    while( running )
    {
        // OpenGL rendering goes here...
        glClear( GL_COLOR_BUFFER_BIT );

        /*
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);
        */

        // Swap front and back rendering buffers
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
        glfwGetWindowParam( GLFW_OPENED );

        glfwSleep(0.1);
    }
    // Close window and terminate GLFW
    glfwTerminate();
    // Exit program
    exit( EXIT_SUCCESS );
}
