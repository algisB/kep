#pragma once
#include "Core.h"
#include <assert.h>
#include <math.h>
namespace Kep
{
    #define real_pow powf
    typedef float real;
    
    class Particle
    {
        Vector3 m_position;
        Vector3 m_velocity;
        Vector3 m_acceleration;
        
        Vector3 m_forceAccum;
        
        real m_damping;
        real m_inverseMass;
        
        void integrate (real _duration);
        void clearAccumulator();
        void addForce(const Vector3 & _force);
    };
};
