#pragma once
#include "Core.h"
#include <assert.h>
//#include <math.h>

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "precision.h"
namespace Kep
{
//#define real_pow powf
//#define real_abs fabsf
//    typedef float real;
    
    class Particle
    {
    public:
        Vector3 m_position;
        Vector3 m_velocity;
        Vector3 m_acceleration;
        
        Vector3 m_forceAccum;
        
        real m_damping;
        real m_inverseMass;
        
        Particle();
        Particle(Vector3 _position, real _mass, real _damping);
        ~Particle();
        
        void integrate (real _duration);
        void clearAccumulator();
        void addForce(const Vector3 & _force);
        real getMass();
        bool hasFiniteMass();
    };
};
