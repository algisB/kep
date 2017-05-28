#include "Particle.h"

using namespace Kep;


Particle::Particle()
{
    m_position = Vector3(0.0f, 0.0f, 0.0f);;
    m_velocity = Vector3(0.0f, 0.0f, 0.0f);
    m_acceleration = Vector3(0.0f, 0.0f, 0.0f);
    
    m_forceAccum = Vector3(0.0f, 0.0f, 0.0f);
    
    m_inverseMass = 0.0f;
    m_damping = 0.0f;
}


Particle::Particle(Vector3 _position, real _mass, real _damping)
{
    m_position = _position;
    m_velocity = Vector3(0.0f, 0.0f, 0.0f);
    m_acceleration = Vector3(0.0f, 0.0f, 0.0f);
    
    m_forceAccum = Vector3(0.0f, 0.0f, 0.0f);
    
    if(_mass > 0.0f)
        m_inverseMass = 1.0f/_mass;
    else
        m_inverseMass = 0.0f;
    m_damping = _damping;
    
}
Particle::~Particle()
{
}

void Particle::integrate(real _duration)
{
    //assert(_duration >= 0.0f);
    
    //update position
    m_position.addScaledVector(m_velocity, _duration);
    
    //update acceleration
    Vector3 resultAcc = m_acceleration;
    resultAcc.addScaledVector(m_forceAccum, m_inverseMass);

    //update linear velocity 
    m_velocity.addScaledVector(resultAcc, _duration);
    
    //add drag
    m_velocity *= real_pow(m_damping, _duration);//real_pow(m_damping, _duration);
    
    clearAccumulator();
    
}
void Particle::clearAccumulator()
{
    m_forceAccum = Vector3(0.0f, 0.0f, 0.0f);
}

void Particle::addForce(const Vector3& _force)
{
    m_forceAccum += _force;
}

real Particle::getMass()
{
    return 1.0f/m_inverseMass;
}

bool Particle::hasFiniteMass()
{
    if(m_inverseMass > 0.0f)
        return true;
    else
        return false;
}

