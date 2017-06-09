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
//gravity
ParticleGravity::ParticleGravity(const Vector3 & _gravity)
{
    m_gravity = _gravity;
}
void ParticleGravity::updateForce(Particle * _particle, real _duration)
{
    _particle->addForce(m_gravity * _particle->getMass());
    
}
//Drag
ParticleDrag::ParticleDrag(real _k1, real _k2)
{
    m_k1 = _k1;
    m_k2 = _k2;
}
void ParticleDrag::updateForce(Particle * _particle, real _duration)
{
    Vector3 force;
    force = _particle->m_velocity;
    
    real dragCoeff  = force.magnitude();
    dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff;
    force.normalize();
    force *= -dragCoeff;
    _particle->addForce(force);
    
}
//Spring

ParticleSpring::ParticleSpring(Particle * _other, real _springConstant, real _restLength)
{
    m_other = _other;
    m_springConstant = _springConstant;
    m_restLength = _restLength;
}

void ParticleSpring::updateForce(Particle * _particle, real _duration)
{
    Vector3 force;
    force = _particle->m_position;
    force -= m_other->m_position;
    
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude-m_restLength);
    magnitude *= m_springConstant;
    
    force.normalize();
    force *= -magnitude;
    _particle->addForce(force);
}
