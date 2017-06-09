#pragma once
#include "Particle.h"
//asdasd
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
    
    class ParticleDrag : public ParticleForceGenerator
    {
    public:
        //velocity drag coefficient
        real m_k1;
        //velocity squared drag coefficient
        real m_k2;

        ParticleDrag(real _k1, real _k2);
        virtual void updateForce(Particle * _particle, real _duration);
    };

    
    class ParticleSpring : public ParticleForceGenerator
    {
      Particle * m_other;
      real m_springConstant;
      real m_restLength;
      
    public:
        ParticleSpring(Particle * _other, real _springConstant, real _restLength);
        virtual void updateForce(Particle * _particle, real _duration);
        
    };
}
