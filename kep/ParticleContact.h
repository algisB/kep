#pragma once

#include "Particle.h"

namespace Kep
{
    class ParticleContact
    {
    public:
        /**
        * Holds the particles that are involved in the contact. The
        * second of these can be NULL, for contacts with the scenery.
        */
        Particle * m_particle[2];
        real m_restitution;
        Vector3 m_contactNormal;
        real m_penetration;
        
        ParticleContact(Particle * _particle0, Particle * _particle1, real _restitution, Vector3 _contactNormal, real _penetration);
        ~ParticleContact();
        
        
        void resolve(real _duration);
        const real calculateSeparatingVelocity();
        void resolveVelocity(real _duration);
    };
    
    class ParticleContactRegistry
    {
    public:
        typedef std::vector<ParticleContact> Registry;
        Registry m_registrations;
        
        ParticleContactRegistry();
        ~ParticleContactRegistry();
        
    };
    
    class ParticleContactResolver
    {
    public:
        unsigned int m_iterations;
        unsigned int m_iterationsUsed;
        ParticleContactRegistry * m_pcr;
        
        ParticleContactResolver(ParticleContactRegistry * _pcr, unsigned int _iterations);
        ~ParticleContactResolver();
        void resolveContacts(real _duration);
    };
    
    

 
    
}
