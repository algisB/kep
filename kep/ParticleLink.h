#pragma once
#include "ParticleContact.h"

namespace Kep
{
    class ParticleLink
    {
    public:
        Particle * m_particle[2];
        ParticleContactRegistry * m_pcr;
        
        ParticleLink(Particle * _particle0, Particle * _particle1, ParticleContactRegistry * _pcr);
        ~ParticleLink();
        real currentLength() const;
        virtual unsigned int update()=0;
    };
    
    class ParticleCable : public ParticleLink
    {
    public:
        real m_maxLength;
        real m_restitution;
        
        ParticleCable(Particle * _particle0, Particle * _particle1, ParticleContactRegistry * _pcr, real _maxLength, real _restitution);
        ~ParticleCable();
        unsigned int update();
        
    };
}
