#pragma once
#include "Particle.h"
#include "ParticleContact.h"
#include "ParticleForceGenerator.h"
#include "ParticleLink.h"
namespace Kep
{
    class ParticleWorld
    {
    public:
        
        
        
        
        
        ParticleWorld(unsigned int _maxContacts, unsigned int _iterations = 0);
        ~ParticleWorld();
        unsigned int generateContacts();
        void integrate(real _duration);
        void runPhysics(real _duration);
        
        
        void startFrame();
    };
    
    
    
    
}
