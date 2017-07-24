#include "ParticleForceGenerator.h"
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

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 * _anchor, real _springConstant, real _restLength)
{
    m_anchor = _anchor;
    m_springConstant = _springConstant;
    m_restLength = _restLength;
}

void ParticleAnchoredSpring::updateForce(Particle * _particle, real _duration)
{
    Vector3 force;
    force = _particle->m_position;
    force -= *m_anchor;
    
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude-m_restLength);
    magnitude *= m_springConstant;
    
    force.normalize();
    force *= -magnitude;
    _particle->addForce(force);
}

ParticleFakeSpring::ParticleFakeSpring(Vector3 * _anchor, real _springConstant, real _damping)
{
    m_anchor = _anchor;
    m_springConstant = _springConstant;
    m_damping = _damping;
}

void ParticleFakeSpring::updateForce(Particle * _particle, real _duration)
{
    if( !_particle->hasFiniteMass())
        return;
    
    Vector3 position =_particle->m_position;
    position -= *m_anchor;
    real gamma = 0.5f * real_sqrt(4 * m_springConstant - m_damping * m_damping);
    if(gamma == 0.0f) return;

    
    Vector3 c = position * (m_damping / (2.0f *gamma)) + _particle->m_velocity * (1.0f / gamma);
    
    Vector3 target = position * real_cos(gamma * _duration) + c * real_sin(gamma * _duration);
    
    
    target *= real_exp(-0.5f * _duration * m_damping);
    
    Vector3 accel = (target - position) * (1.0f / _duration*_duration) - _particle->m_velocity * _duration;
    
    _particle->addForce(accel * _particle->getMass());
    
    
}
