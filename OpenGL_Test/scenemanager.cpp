#include "scenemanager.h"

#include "btBulletDynamicsCommon.h"

#define GLEW_STATIC
#include "3rd_party/glew.c"
#include <GL/glfw.h>

#include <stdlib.h>
#include <iostream>


SceneManager::SceneManager()
{
    initGl();

    int i;

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));

    ///create a few basic rigid bodies
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));

    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-56,0));

    {
        btScalar mass(0.);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass,localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);
    }

    {
        //create a dynamic rigidbody

        //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
        btCollisionShape* colShape = new btSphereShape(btScalar(1.));
        collisionShapes.push_back(colShape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();

        btScalar	mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            colShape->calculateLocalInertia(mass,localInertia);

            startTransform.setOrigin(btVector3(2,10,0));

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
            btRigidBody* body = new btRigidBody(rbInfo);

            dynamicsWorld->addRigidBody(body);
    }

    struct Vertex
    {
        float x, y, z;        // Vertex
        float nx, ny, nz;     // Normal
        float s0, t0;         // Texcoord0
        float s1, t1;         // Texcoord1
        float s2, t2;         // Texcoord2
        float padding[4];     // Make sure vertex size is a multiple of 16 (16 floats)
    };

    int num_verts = 8;
    Vertex* verts = new Vertex[num_verts];

    verts[0].x = -1.0f; verts[0].y = -1.0f; verts[0].z = -1.0f;
    verts[1].x = -1.0f; verts[1].y = -1.0f; verts[1].z =  1.0f;
    verts[2].x = -1.0f; verts[2].y =  1.0f; verts[2].z = -1.0f;
    verts[3].x = -1.0f; verts[3].y =  1.0f; verts[3].z =  1.0f;
    verts[4].x =  1.0f; verts[4].y = -1.0f; verts[4].z = -1.0f;
    verts[5].x =  1.0f; verts[5].y = -1.0f; verts[5].z =  1.0f;
    verts[6].x =  1.0f; verts[6].y =  1.0f; verts[6].z = -1.0f;
    verts[7].x =  1.0f; verts[7].y =  1.0f; verts[7].z =  1.0f;

    int num_indexes = 8;
    short* indexes = new short[num_indexes];

    indexes[0] = 0;
    indexes[1] = 1;
    indexes[2] = 2;
    indexes[3] = 3;
    indexes[4] = 4;
    indexes[5] = 5;
    indexes[6] = 6;
    indexes[7] = 7;

    int verts_size = sizeof(Vertex) * num_verts;

    // generate a new VBO and get the associated ID
    GLuint verts_vbo;
    glGenBuffers(1, &verts_vbo);

    // bind VBO in order to use
    glBindBuffer(GL_ARRAY_BUFFER, verts_vbo);

    // upload data to VBO
    glBufferData(GL_ARRAY_BUFFER, verts_size, verts, GL_STATIC_DRAW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &verts[0].x);
    /*
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, verts_size, &vertex[0].nx);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, verts_size, &vertex[0].s0);
    glClientActiveTexture(GL_TEXTURE1);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, verts_size), &vertex[0].s1);
    glClientActiveTexture(GL_TEXTURE2);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, verts_size, &vertex[0].s2);
    */
    glDrawElements(GL_POINTS, num_verts, GL_UNSIGNED_SHORT, indexes);

    glFlush();
    glfwSwapBuffers();

    glfwSleep(5.0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glDeleteBuffers(1, &verts_vbo);

    while (false)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        dynamicsWorld->stepSimulation(1.f / 60.f,10);




        //print positions of all objects
        /*
        for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                btTransform trans;
                body->getMotionState()->getWorldTransform(trans);
                printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
            }
        }
        */
        glFlush();
        glfwSwapBuffers();

        //glfwSetTime(0.0);// Sets time to zero, so we know later how much time the frame took
        //glfwGetTime();

        glfwSleep(0.1);

        if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {break;}
    }

    //cleanup in the reverse order of creation/initialization

    //remove the rigidbodies from the dynamics world and delete them
    for (i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject( obj );
        delete obj;
    }

    //delete collision shapes
    for (int j=0;j<collisionShapes.size();j++)
    {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    //delete dynamics world
    delete dynamicsWorld;

    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    //next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();

    endGl();
}

void SceneManager::initGl()
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

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}



void SceneManager::endGl()
{
    glfwCloseWindow();
    glfwTerminate();
}

SceneManager::~SceneManager()
{
}
