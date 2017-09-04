#include "RigidBody.h"
using namespace Kep;


RigidBody::RigidBody(Vector3 _position, real _mass)
{
    position = _position;
    
    velocity = Vector3(0.0f, 0.0f, 0.0f);
    acceleration = Vector3(0.0f, 0.0f, 0.0f);
    
    forceAccum = Vector3(0.0f, 0.0f, 0.0f);
    
    //TODO: rot
    
    
    if(_mass > 0.0f)
        inverseMass = 1.0f/_mass;
    else
        inverseMass = 0.0f;
}
void RigidBody::calculateDerivedData()
{
    transformMatrix.setOrientationAndPos(orientation, position);
    transformInertiaTensor(inverseInertiaTensorWorld,
                           orientation,
                           inverseInertiaTensor,
                           transformMatrix);
}

void RigidBody::setInertiaTensor(const Matrix3 &_inertiaTensor)
{
    inverseInertiaTensor.setInverse(_inertiaTensor);
}

void RigidBody::transformInertiaTensor(Matrix3 &_iitWorld,
                                    const Quaternion &_q,
                                    const Matrix3 &_iitBody,
                                    const Matrix4 &_rotmat)
{
    real t4 = _rotmat.data[0]*_iitBody.data[0]+
    _rotmat.data[1]*_iitBody.data[3]+
    _rotmat.data[2]*_iitBody.data[6];
    real t9 = _rotmat.data[0]*_iitBody.data[1]+
    _rotmat.data[1]*_iitBody.data[4]+
    _rotmat.data[2]*_iitBody.data[7];
    real t14 = _rotmat.data[0]*_iitBody.data[2]+
    _rotmat.data[1]*_iitBody.data[5]+
    _rotmat.data[2]*_iitBody.data[8];
    real t28 = _rotmat.data[4]*_iitBody.data[0]+
    _rotmat.data[5]*_iitBody.data[3]+
    _rotmat.data[6]*_iitBody.data[6];
    real t33 = _rotmat.data[4]*_iitBody.data[1]+
    _rotmat.data[5]*_iitBody.data[4]+
    _rotmat.data[6]*_iitBody.data[7];
    real t38 = _rotmat.data[4]*_iitBody.data[2]+
    _rotmat.data[5]*_iitBody.data[5]+
    _rotmat.data[6]*_iitBody.data[8];
    
    real t52 = _rotmat.data[8]*_iitBody.data[0]+
    _rotmat.data[9]*_iitBody.data[3]+
    _rotmat.data[10]*_iitBody.data[6];
    real t57 = _rotmat.data[8]*_iitBody.data[1]+
    _rotmat.data[9]*_iitBody.data[4]+
    _rotmat.data[10]*_iitBody.data[7];
    real t62 = _rotmat.data[8]*_iitBody.data[2]+
    _rotmat.data[9]*_iitBody.data[5]+
    _rotmat.data[10]*_iitBody.data[8];

    _iitWorld.data[0] = t4*_rotmat.data[0]+
    t9*_rotmat.data[1]+
    t14*_rotmat.data[2];
    _iitWorld.data[1] = t4*_rotmat.data[4]+
    t9*_rotmat.data[5]+
    t14*_rotmat.data[6];
    _iitWorld.data[2] = t4*_rotmat.data[8]+
    t9*_rotmat.data[9]+
    t14*_rotmat.data[10];
    _iitWorld.data[3] = t28*_rotmat.data[0]+
    t33*_rotmat.data[1]+
    t38*_rotmat.data[2];
    _iitWorld.data[4] = t28*_rotmat.data[4]+
    t33*_rotmat.data[5]+
    t38*_rotmat.data[6];
    _iitWorld.data[5] = t28*_rotmat.data[8]+
    t33*_rotmat.data[9]+
    t38*_rotmat.data[10];
    _iitWorld.data[6] = t52*_rotmat.data[0]+
    t57*_rotmat.data[1]+
    t62*_rotmat.data[2];
    _iitWorld.data[7] = t52*_rotmat.data[4]+
    t57*_rotmat.data[5]+
    t62*_rotmat.data[6];
    _iitWorld.data[8] = t52*_rotmat.data[8]+
    t57*_rotmat.data[9]+
    t62*_rotmat.data[10];

    

}

void RigidBody::addForce(const Vector3 &_force)
{
    forceAccum += _force;
}

void RigidBody::addForceAtPoint(const Vector3 &_force,
                                const Vector3 &_point)
{
    
}

void RigidBody::addForceAtBodyPoint(const Vector3 &_force, const Vector3 &_point)
{
    Vector3 pt = Kep::localToWorld(_point, transformMatrix);
    addForceAtPoint(_force, pt);
}

void RigidBody::integrate(real _duration)
{
    //update position
    position.addScaledVector(velocity, _duration);
    
    //update acceleration
    Vector3 resultAcc = acceleration;
    resultAcc.addScaledVector(forceAccum, inverseMass);

    //update linear velocity 
    velocity.addScaledVector(resultAcc, _duration);
    
    //add drag
    //velocity *= real_pow(damping, _duration);//real_pow(m_damping, _duration);
    
    clearAccumulators();
}
void RigidBody::clearAccumulators()
{
    forceAccum = Vector3(0,0,0);
    torqueAccum = Vector3(0,0,0);
}

real RigidBody::getMass()
{
    return 1.0f/inverseMass;
}

bool RigidBody::hasFiniteMass()
{
    if(inverseMass > 0.0f)
        return true;
    else
        return false;
}
