#include "btBulletDynamicsCommon.h"

#include "glmanager.h"
#include "colladaloader.h"

#include <stdlib.h>
#include <iostream>

#include <QString>
#include <QFile>

int main( void )
{
    GlManager gl;// Initiates opengl instance

    ColladaLoader* cl = new ColladaLoader("c:/dae_samples/cube.dae");

    // Main loop

    delete cl;
    delete gl;
}
