#pragma once
#include <stdio.h>
#include <stdlib.h>
//#include <cmath>
#include "precision.h"
namespace Kep
{
    //typedef float real;
    
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
        Vector3 operator *(const real _value);
        void operator +=(const Vector3 & _v);
        
        Vector3 operator +(const Vector3 & _v);
        
        void operator -=(const Vector3 & _v);
        
        Vector3 operator -(const Vector3 & _v);
        
        void invert();
        
        real magnitude();
        
        real squareMagnitude();
        void normalize();
        
        void addScaledVector(const Vector3 & _vector, const real _scale);
        
        Vector3 componentProduct(const Vector3 & _vector);
        
        real scalarProduct(const Vector3 & _vector);
        
        real operator * (const Vector3 & _vector);

        Vector3 vectorProduct(const Vector3 & _vector);

        void operator %=(const Vector3 & _vector);
        
        Vector3 operator %(const Vector3 & _vector);
        
        void dump();
    };
    
    class Quaternion
    {
    public:
        union
        {
            struct
            {
                real r;
                
                real i;
                real j;
                real k;
            };
            real data[4];
        };
        
        Quaternion(real _r = 0.0f, real _i = 0.0f, real _j = 0.0f, real _k = 0.0f);
        ~Quaternion();
        void normalize();
        void operator *= (const Quaternion &_multiplier);
        void rotateByVector(const Vector3 &_vector);
        void addScaledVector(const Vector3 &_vector, real _scale);
        void setEuler(Vector3 _axis, real _angle);
    };
    
    class Matrix3
    {
    public:
        real data[9];
        
        Matrix3(    
        real _d0 = 1.0f, real _d1 = 0.0f, real _d2 = 0.0f,
        real _d3 = 0.0f, real _d4 = 1.0f, real _d5 = 0.0f,
        real _d6 = 0.0f, real _d7 = 0.0f, real _d8 = 1.0f
        );
        ~Matrix3();
        
        Matrix3 operator*(const Matrix3 &_o) const;
        
        
        
        real determinant() const;
        Matrix3 transpose() const;
        Matrix3 cofactor() const;
        void setInverse(const Matrix3 & _m);
        Matrix3 inverse() const;
        void invert();
        
        void setOrientation(const Quaternion &_q);
        
        void dump();
    };
    
    class Matrix4
    {
    public:
        real data[16];
        
        Matrix4(    
        real _d0 = 1.0f, real _d1 = 0.0f, real _d2 = 0.0f, real _d3 = 0.0f,
        real _d4 = 0.0f, real _d5 = 1.0f, real _d6 = 0.0f, real _d7 = 0.0f,
        real _d8 = 0.0f, real _d9 = 0.0f, real _d10 = 1.0f, real _d11 = 0.0f,
        real _d12 = 0.0f, real _d13 = 0.0f, real _d14 = 0.0f, real _d15 = 1.0f
        );
        
        ~Matrix4();
        Vector3 operator*(const Vector3 &_vector) const;
        Matrix4 operator*(const Matrix4 &_o) const;
        real determinant() const;
        Matrix4 transpose() const;
        Matrix4 cofactor() const;
        void setInverse(const Matrix4 &_m);
        Matrix4 inverse() const;
        void invert();
        
        void setOrientationAndPos(const Quaternion &_q, const Vector3 &_pos);
        
        Vector3 transformInverseDirection(const Vector3 &_vector) const;
        Vector3 transformDirection(const Vector3 &_vector)const;
        
        
        void dump();
        
    };
    
    inline Vector3 localToWorld(const Vector3 &_local, const Matrix4 &_transform)
    {
        return _transform * _local;
    }
    inline Vector3 worldToLocal(const Vector3 &_world, const Matrix4 &_transform)
    {
        Matrix4 inverseTransform;
        inverseTransform.setInverse(_transform);
        
        return inverseTransform * _world;
    }
    
}
