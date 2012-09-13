#include "glmanager.h"

#define GLEW_STATIC
#include "3rd_party/glew.c"
#include <GL/glfw.h>

/*
// function pointers for VBO Extension
// Windows needs to get function pointers from ICD OpenGL drivers,
// because opengl32.dll does not support extensions higher than v1.1.
#ifdef _WIN32

// VBO Extension Function Pointers
PFNGLGENBUFFERSARBPROC glGenBuffersARB = 0;
PFNGLBINDBUFFERARBPROC glBindBufferARB = 0;
PFNGLBUFFERDATAARBPROC glBufferDataARB = 0;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = 0;

/*
PFNGLGENBUFFERSARBPROC            pglGenBuffersARB = 0;             // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC            pglBindBufferARB = 0;             // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC            pglBufferDataARB = 0;             // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAARBPROC         pglBufferSubDataARB = 0;          // VBO Sub Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC         pglDeleteBuffersARB = 0;          // VBO Deletion Procedure
PFNGLGETBUFFERPARAMETERIVARBPROC  pglGetBufferParameterivARB = 0;   // return various parameters of VBO
PFNGLMAPBUFFERARBPROC             pglMapBufferARB = 0;              // map VBO procedure
PFNGLUNMAPBUFFERARBPROC           pglUnmapBufferARB = 0;            // unmap VBO procedure

#define glGenBuffersARB           pglGenBuffersARB
#define glBindBufferARB           pglBindBufferARB
#define glBufferDataARB           pglBufferDataARB
#define glBufferSubDataARB        pglBufferSubDataARB
#define glDeleteBuffersARB        pglDeleteBuffersARB
#define glGetBufferParameterivARB pglGetBufferParameterivARB
#define glMapBufferARB            pglMapBufferARB
#define glUnmapBufferARB          pglUnmapBufferARB


#endif
*/

#include <stdlib.h>
#include <iostream>

GlManager::GlManager()
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

    GLuint vboId;                              // ID of VBO
    GLfloat* vertices = new GLfloat[vCount*3]; // create vertex array
    ...

    // generate a new VBO and get the associated ID
    glGenBuffersARB(1, &vboId);

    // bind VBO in order to use
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

    // upload data to VBO
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, dataSize, vertices, GL_STATIC_DRAW_ARB);

    // it is safe to delete after copying data to VBO
    delete [] vertices;
    ...

    //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void GlManager::~GlManager()
{
    // delete VBO when program terminated
    glDeleteBuffersARB(1, &vboId);
}
