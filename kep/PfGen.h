#pragma once
#include "Particle.h"

namespace Kep 
{
    class ParticleForceGenerator
    {
    public:
        virtual void updateForce(Particle * _particle, real _duration) = 0;
    };
    
    class ParticleForceRegistry
    {
    public:
        struct ParticleForceRegistration
        {
            Particle * particle;
            ParticleForceGenerator * fg;
        };
        
        typedef std::vector<ParticleForceRegistration> Registry;
        Registry m_registrations;
        
        ParticleForceRegistry();
        
        void updateForces(real _duration);
        
        
        void add(Particle * _particle, ParticleForceGenerator * _fg);
        void remove(Particle * _particle, ParticleForceGenerator * _fg);
        void clear();
        
    };

    
    
    ////////////////////
    //Derived generators
    ////////////////////
    class ParticleGravity : public ParticleForceGenerator
    {
    public:
        Vector3 m_gravity;
        ParticleGravity(const Vector3 & _gravity);
        virtual void updateForce(Particle * _particle, real _duration);
    };
}
