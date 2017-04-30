#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
namespace Kep
{
    typedef float real;
    
    class Vector3
    {
    public:
        real m_x;
        real m_y;
        real m_z;
    private:
        real pad;
    public:
        Vector3() : m_x(0) , m_y(0), m_z(0){}
        Vector3(real _x, real _y, real _z) : m_x(_x), m_y(_y), m_z(_z){}
        ~Vector3(){}
        
        void operator *=(const real _value);
        const Vector3 operator *(const real _value);
        void operator +=(const Vector3 & _v);
        
        const Vector3 operator +(const Vector3 & _v);
        
        void operator -=(const Vector3 & _v);
        
        const Vector3 operator -(const Vector3 & _v);
        
        void invert();
        
        const real magnitude();
        
        const real squareMagnitude();
        void normalize();
        
        void addScaledVector(const Vector3 & _vector, const real _scale);
        
        const Vector3 componentProduct(const Vector3 & _vector);
        
        const real scalarProduct(const Vector3 & _vector);
        
        const real operator * (const Vector3 & _vector);

        const Vector3 vectorProduct(const Vector3 & _vector);

        void operator %=(const Vector3 & _vector);
        
        const Vector3 operator %(const Vector3 & _vector);
        
        void dump();
    };
}
