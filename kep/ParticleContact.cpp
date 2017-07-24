#include "ParticleContact.h"
using namespace Kep;

ParticleContact::ParticleContact(Particle * _particle0, Particle * _particle1, real _restitution, Vector3 _contactNormal, real _penetration)
{
    m_particle[0] = _particle0;
    m_particle[1] = _particle1;
    m_restitution = _restitution;
    m_contactNormal = _contactNormal;
    m_penetration = _penetration;
}

ParticleContact::~ParticleContact()
{
    
}

void ParticleContact::resolve(real _duration)
{
    resolveVelocity(_duration);
}

const real ParticleContact::calculateSeparatingVelocity()
{
    Vector3 relativeVelocity = m_particle[0]->m_velocity;
    if(m_particle[1] != NULL)
        relativeVelocity -= m_particle[1]->m_velocity;
    return relativeVelocity * m_contactNormal;
}

void ParticleContact::resolveVelocity(real _duration)
{
    real separatingVelocity = calculateSeparatingVelocity();
    if(separatingVelocity > 0.0f)
    {
        return;
    }
    
    
    real newSepVelocity = -separatingVelocity*m_restitution;
    
    
    /////////////////////////
    Vector3 accCausedVelocity = m_particle[0]->m_acceleration;
    if(m_particle[1] != NULL)
        accCausedVelocity -= m_particle[1]->m_acceleration;
    
    real accCausedSepVelocity = accCausedVelocity * m_contactNormal * _duration;
    
    
    if(accCausedSepVelocity)
    {
        newSepVelocity += m_restitution * accCausedSepVelocity;
        if(newSepVelocity < 0)
            newSepVelocity = 0;
    }
    //////////////////////////
    
    
    real deltaVelocity = newSepVelocity - separatingVelocity;
    real totalInverseMass = m_particle[0]->m_inverseMass;
    
    if(m_particle[1] != NULL)
        totalInverseMass += m_particle[1]->m_inverseMass;
    
    if(totalInverseMass <= 0)
        return;
    
    
    
    real impulse = deltaVelocity / totalInverseMass;
    
    Vector3 impulsePerIMass = m_contactNormal * impulse;
    
    m_particle[0]->m_velocity = m_particle[0]->m_velocity + impulsePerIMass * m_particle[0]->m_inverseMass;
    
    if(m_particle[1] != NULL)
    {
        m_particle[1]->m_velocity = m_particle[1]->m_velocity + impulsePerIMass * -m_particle[1]->m_inverseMass;
    }
}




ParticleContactRegistry::ParticleContactRegistry()
{
}

ParticleContactRegistry::~ParticleContactRegistry()
{
}



ParticleContactResolver::ParticleContactResolver(ParticleContactRegistry * _pcr, unsigned int _iterations)
{
    m_iterations = _iterations;
    m_pcr = _pcr;
}
ParticleContactResolver::~ParticleContactResolver()
{
    
}

void ParticleContactResolver::resolveContacts(real _duration)
{
    m_iterationsUsed = 0;
    
    while(m_iterationsUsed < m_iterations)
    {
        real max = 0.0f;
        unsigned int maxIndex = 0;
        
        for(unsigned int i = 0; i < m_pcr->m_registrations.size(); i++)
        {
            real sepVel = m_pcr->m_registrations[i].calculateSeparatingVelocity();
            if(sepVel < max)
            {
                max = sepVel;
                maxIndex = i;
            }
        }
        
        if(m_pcr->m_registrations.size() > 0)
        {
            m_pcr->m_registrations[maxIndex].resolve(_duration);//resolve
            m_pcr->m_registrations.erase(m_pcr->m_registrations.begin()+maxIndex);//and remove from registry //TODO: use are link list for faster operation
        }
        m_iterationsUsed++;
    }
    
    
//     /*for(unsigned int i = 0; i < m_pcr->m_registrations.size(); i++)
//     {
//         real max = 0.0f;          
//         unsigned int maxIndex = 0;
//         
//         m_pcr->m_registrations[i].resolve(_duration);//resolve
//         m_pcr->m_registrations.erase(m_pcr->m_registrations.begin()+i);//and remove from registry //TODO: use are link list for faster operation
//     }*/
    //m_pcr->m_registrations.clear();
}









