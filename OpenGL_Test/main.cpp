#include "btBulletDynamicsCommon.h"

#include "glmanager.h"
#include "colladaloader.h"

#include <stdlib.h>
#include <iostream>

#include <QString>
#include <QFile>

int main( void )
{
    GlManager gl;
    gl.init();

    ColladaLoader* cl = new ColladaLoader("c:/dae_samples/cube.dae");
    delete cl;


}
