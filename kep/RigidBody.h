#pragma once
#include "Core.h"
namespace Kep
{
    class RigidBody
    {
    public:
        real inverseMass;
        
        Vector3 position;
        Quaternion orientation;
        
        Vector3 velocity;
        Vector3 angularVelocity;
        
        Vector3 acceleration;
        Vector3 angularAcceleration;
        
        Vector3 forceAccum;
        Vector3 torqueAccum;
        
        
        Matrix4 transformMatrix;
        
        Matrix3 inverseInertiaTensor;
        Matrix3 inverseInertiaTensorWorld;
        

        
        RigidBody(Vector3 _position = Vector3(0.0f,0.0f,0.0f), real _mass = 1.0f);
        void calculateDerivedData();
        void setInertiaTensor(const Matrix3 &_inertiaTensor);
        
        void transformInertiaTensor(Matrix3 &_iitWorld,
                                    const Quaternion &_q,
                                    const Matrix3 &_iitBody,
                                    const Matrix4 &_rotmat);
        
        void addForce(const Vector3 &_force);
        void addForceAtPoint(const Vector3 &_force,
                             const Vector3 &_point);
        void addForceAtBodyPoint(const Vector3 &_force,
                                 const Vector3 &_point);
        
        void integrate(real _duration);
        void clearAccumulators();
        real getMass();
        bool hasFiniteMass();
    };
}
