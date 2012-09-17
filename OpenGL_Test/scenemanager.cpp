#include "scenemanager.h"

#include "btBulletDynamicsCommon.h"

#define GLEW_STATIC
#include "3rd_party/glew.c"
#include <GL/glfw.h>

#include <stdlib.h>
#include <iostream>


#define BUFFER_OFFSET(i) ((char *)NULL + (i))


SceneManager::SceneManager()
{
    initGl();

    int i;

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new    btCollisionDispatcher(collisionConfiguration);

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

        btScalar    mass(1.f);

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
        GLfloat x, y, z;    // Vertex
        GLfloat nx, ny, nz; // Normal
        GLfloat cr, cg, cb, ca; // Color
        GLfloat tu0, tv0;   // Texcoord0
        GLfloat tu1, tv1;   // Texcoord1
        GLfloat tu2, tv2;   // Texcoord2
        // Make sure sizeof(Vertex) is a multiple of 16
    };
/*
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
    GLushort* indexes = new GLushort[num_indexes];

    indexes[0] = 0;
    indexes[1] = 1;
    indexes[2] = 2;
    indexes[3] = 3;
    indexes[4] = 4;
    indexes[5] = 5;
    indexes[6] = 6;
    indexes[7] = 7;
*/

    int num_verts = 24;
    Vertex* verts = new Vertex[num_verts];

    // Top
    verts[0].x = 1; verts[0].y = 1; verts[0].z = -1;
    verts[0].nx = 0; verts[0].ny = 1; verts[0].nz = 0;
    verts[0].tu0 = 0; verts[0].tv0 = 0;

    verts[1].x = -1; verts[1].y = 1; verts[1].z = -1;
    verts[1].nx = 0; verts[1].ny = 1; verts[1].nz = 0;
    verts[1].tu0 = 0; verts[1].tv0 = 1;

    verts[2].x = -1; verts[2].y = 1; verts[2].z = 1;
    verts[2].nx = 0; verts[2].ny = 1; verts[2].nz = 0;
    verts[2].tu0 = 1; verts[2].tv0 = 1;

    verts[3].x = 1; verts[3].y = 1; verts[3].z = 1;
    verts[3].nx = 0; verts[3].ny = 1; verts[3].nz = 0;
    verts[3].tu0 = 1; verts[3].tv0 = 0;

    // Bottom
    verts[4].x = 1; verts[4].y = -1; verts[4].z = 1;
    verts[4].nx = 0; verts[4].ny = -1; verts[4].nz = 0;
    verts[4].tu0 = 0; verts[4].tv0 = 0;

    verts[5].x = -1; verts[5].y = -1; verts[5].z = 1;
    verts[5].nx = 0; verts[5].ny = -1; verts[5].nz = 0;
    verts[5].tu0 = 0; verts[5].tv0 = 1;

    verts[6].x = -1; verts[6].y = -1; verts[6].z = -1;
    verts[6].nx = 0; verts[6].ny = -1; verts[6].nz = 0;
    verts[6].tu0 = 1; verts[6].tv0 = 1;

    verts[7].x = 1; verts[7].y = -1; verts[7].z = -1;
    verts[7].nx = 0; verts[7].ny = -1; verts[7].nz = 0;
    verts[7].tu0 = 1; verts[7].tv0 = 0;

    // Front
    verts[8].x = 1; verts[8].y = 1; verts[8].z = 1;
    verts[8].nx = 0; verts[8].ny = 0; verts[8].nz = 1;
    verts[8].tu0 = 0; verts[8].tv0 = 0;

    verts[9].x = -1; verts[9].y = 1; verts[9].z = 1;
    verts[9].nx = 0; verts[9].ny = 0; verts[9].nz = 1;
    verts[9].tu0 = 0; verts[9].tv0 = 1;

    verts[10].x = -1; verts[10].y = -1; verts[10].z = 1;
    verts[10].nx = 0; verts[10].ny = 0; verts[10].nz = 1;
    verts[10].tu0 = 1; verts[10].tv0 = 1;

    verts[11].x = 1; verts[11].y = -1; verts[11].z = 1;
    verts[11].nx = 0; verts[11].ny = 0; verts[11].nz = 1;
    verts[11].tu0 = 1; verts[11].tv0 = 0;

    // Back
    verts[12].x = 1; verts[12].y = -1; verts[12].z = -1;
    verts[12].nx = 0; verts[12].ny = 0; verts[12].nz = -1;
    verts[12].tu0 = 0; verts[12].tv0 = 0;

    verts[13].x = -1; verts[13].y = -1; verts[13].z = -1;
    verts[13].nx = 0; verts[13].ny = 0; verts[13].nz = -1;
    verts[13].tu0 = 0; verts[13].tv0 = 1;

    verts[14].x = -1; verts[14].y = 1; verts[14].z = -1;
    verts[14].nx = 0; verts[14].ny = 0; verts[14].nz = -1;
    verts[14].tu0 = 1; verts[14].tv0 = 1;

    verts[15].x = 1; verts[15].y = 1; verts[15].z = -1;
    verts[15].nx = 0; verts[15].ny = 0; verts[15].nz = -1;
    verts[15].tu0 = 1; verts[15].tv0 = 0;

    // Left
    verts[16].x = -1; verts[16].y = 1; verts[16].z = 1;
    verts[16].nx = -1; verts[16].ny = 0; verts[16].nz = 0;
    verts[16].tu0 = 0; verts[16].tv0 = 0;

    verts[17].x = -1; verts[17].y = 1; verts[17].z = -1;
    verts[17].nx = -1; verts[17].ny = 0; verts[17].nz = 0;
    verts[17].tu0 = 0; verts[17].tv0 = 1;

    verts[18].x = -1; verts[18].y = -1; verts[18].z = -1;
    verts[18].nx = -1; verts[18].ny = 0; verts[18].nz = 0;
    verts[18].tu0 = 1; verts[18].tv0 = 1;

    verts[19].x = -1; verts[19].y = -1; verts[19].z = 1;
    verts[19].nx = -1; verts[19].ny = 0; verts[19].nz = 0;
    verts[19].tu0 = 1; verts[19].tv0 = 0;

    // Right
    verts[20].x = 1; verts[20].y = 1; verts[20].z = -1;
    verts[20].nx = 1; verts[20].ny = 0; verts[20].nz = 0;
    verts[20].tu0 = 0; verts[20].tv0 = 0;

    verts[21].x = 1; verts[21].y = 1; verts[21].z = 1;
    verts[21].nx = 1; verts[21].ny = 0; verts[21].nz = 0;
    verts[21].tu0 = 0; verts[21].tv0 = 1;

    verts[22].x = 1; verts[22].y = -1; verts[22].z = 1;
    verts[22].nx = 1; verts[22].ny = 0; verts[22].nz = 0;
    verts[22].tu0 = 1; verts[22].tv0 = 1;

    verts[23].x = 1; verts[23].y = -1; verts[23].z = -1;
    verts[23].nx = 1; verts[23].ny = 0; verts[23].nz = 0;
    verts[23].tu0 = 1; verts[23].tv0 = 0;

    // Colours
    for (int i = 0; i < 24; i++)
    {
        verts[i].cr = 1.0;
        verts[i].cg = 1.0;
        verts[i].cb = 1.0;
        verts[i].ca = 1.0;
    }


    int num_indexes = 36;
    GLushort* indexes = new GLushort[num_indexes];

    // Index Array (define our triangles)
    // A Face looks like (numbers are the array index number of the vertex)
    // 1      2
    // +------+
    // |      |
    // |      |
    // +------+
    // 0      3
    indexes[0] = 0; indexes[1] = 1; indexes[2] = 2;
    indexes[3] = 2; indexes[4] = 3; indexes[5] = 0;

    indexes[6] = 4; indexes[7] = 5; indexes[8] = 6;
    indexes[9] = 6; indexes[10] = 7; indexes[11] = 4;

    indexes[12] = 8; indexes[13] = 9; indexes[14] = 10;
    indexes[15] = 10; indexes[16] = 11; indexes[17] = 8;

    indexes[18] = 12; indexes[19] = 13; indexes[20] = 14;
    indexes[21] = 14; indexes[22] = 15; indexes[23] = 12;

    indexes[24] = 16; indexes[25] = 17; indexes[26] = 18;
    indexes[27] = 18; indexes[28] = 19; indexes[29] = 16;

    indexes[30] = 20; indexes[31] = 21; indexes[32] = 22;
    indexes[33] = 22; indexes[34] = 23; indexes[35] = 20;




    int verts_size = sizeof(Vertex) * num_verts;
    int indexes_size = sizeof(GLushort) * num_indexes;

    // generate a new VBO and get the associated ID
    GLuint verts_vbo;
    glGenBuffers(1, &verts_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, verts_vbo);
    glBufferData(GL_ARRAY_BUFFER, verts_size, verts, GL_STATIC_DRAW);

    GLuint indexes_vbo;
    glGenBuffers(1, &indexes_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_size, indexes, GL_STATIC_DRAW);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(0.0, 1.0, 1.0, 1.0);


    glBindBuffer(GL_ARRAY_BUFFER, verts_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_vbo);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(GLfloat) * 9));
    //glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(GLfloat) * 3));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(GLfloat) * 6));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(GLfloat) * 0));
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
    glDrawElements(GL_TRIANGLES, num_verts, GL_UNSIGNED_SHORT, indexes);

    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    glFlush();
    glfwSwapBuffers();
    glFlush();

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
    //glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
}



void SceneManager::endGl()
{
    glfwCloseWindow();
    glfwTerminate();
}

SceneManager::~SceneManager()
{
}
