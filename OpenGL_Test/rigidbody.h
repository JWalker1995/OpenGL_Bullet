#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "btBulletDynamicsCommon.h"

class RigidBody : public btRigidBody
{
public:
    RigidBody(const btRigidBodyConstructionInfo &info);
};

#endif // RIGIDBODY_H
