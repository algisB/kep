#include "ParticleLink.h"
using namespace Kep;


ParticleLink::ParticleLink(Particle * _particle0, Particle * _particle1, ParticleContactRegistry * _pcr)
{
    m_particle[0] = _particle0;
    m_particle[1] = _particle1;
    m_pcr = _pcr;
    
}
real ParticleLink::currentLength() const
{
    Vector3 relativePos = m_particle[0]->m_position - m_particle[1]->m_position;
    return relativePos.magnitude();
}

ParticleCable::ParticleCable(Particle * _particle0, Particle * _particle1, ParticleContactRegistry * _pcr, real _maxLength, real _restitution) : ParticleLink(_particle0, _particle1, _pcr)
{
    m_maxLength = _maxLength;
    m_restitution = _restitution;
}


unsigned int ParticleCable::update()
{
     real length = currentLength();
     if(length < m_maxLength)
         return 0;
     
    Vector3 normal = (m_particle[1]->m_position - m_particle[0]->m_position);    
    normal.normalize();
    
    ParticleContact pc(m_particle[0],m_particle[1], m_restitution, normal, (length - m_maxLength));
    m_pcr->m_registrations.push_back(pc);
    
    return 1;
}
