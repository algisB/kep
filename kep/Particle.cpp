#include "Particle.h"

using namespace Kep;

void Particle::integrate(real _duration)
{
    assert(_duration > 0.0f);
    
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


