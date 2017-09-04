#pragma once
#include "RigidBody.h"
#include <vector>
namespace Kep 
{
    class ForceGenerator
    {
    public:
        virtual void updateForce(RigidBody * _rigidBody, real _duration) = 0;
    };
    
    class ForceRegistry
    {
    public:
        struct ForceRegistration
        {
            RigidBody * rigidBody;
            ForceGenerator * fg;
        };
        
        typedef std::vector<ForceRegistration> Registry;
        Registry m_registrations;
        
        ForceRegistry();
        
        void updateForces(real _duration);
        
        
        void add(RigidBody * _rigidBody, ForceGenerator * _fg);
        void remove(RigidBody * _rigidBody, ForceGenerator * _fg);
        void clear();
        
    };

    
    
    ////////////////////
    //Derived generators
    ////////////////////
    class Gravity : public ForceGenerator
    {
    public:
        Vector3 m_gravity;
        Gravity(const Vector3 & _gravity);
        virtual void updateForce(RigidBody * _rigidBody, real _duration);
    };
    
    class Drag : public ForceGenerator
    {
    public:
        //velocity drag coefficient
        real m_k1;
        //velocity squared drag coefficient
        real m_k2;

        Drag(real _k1, real _k2);
        virtual void updateForce(RigidBody * _rigidBody, real _duration);
    };

}

