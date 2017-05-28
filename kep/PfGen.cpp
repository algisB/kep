#include "PfGen.h"
using namespace Kep;


Kep::ParticleForceRegistry::ParticleForceRegistry()
{
}

void ParticleForceRegistry::updateForces(real _duration)
{
    for(int i = 0; i<m_registrations.size(); i++)
    {
        ParticleForceRegistration * rtmp = &m_registrations[i];
        rtmp->fg->updateForce(rtmp->particle, _duration);
    }
}


void ParticleForceRegistry::add(Particle * _particle, ParticleForceGenerator * _fg)
{
    ParticleForceRegistration pfr;
    pfr.fg = _fg;
    pfr.particle = _particle;
    m_registrations.push_back(pfr);
}
////////////////////
//Derived generators
////////////////////
ParticleGravity::ParticleGravity(const Vector3 & _gravity)
{
    m_gravity = _gravity;
}
void ParticleGravity::updateForce(Particle * _particle, real _duration)
{
    _particle->addForce(m_gravity * _particle->getMass());
    
}
