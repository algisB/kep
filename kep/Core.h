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
    
    class Matrix3
    {
    public:
        real data[9];
        
        Matrix3();
        Matrix3(    
        real _d0, real _d1, real _d2,
        real _d3, real _d4, real _d5,
        real _d6, real _d7, real _d8
        );
        ~Matrix3();
        
        Matrix3 operator*(const Matrix3 &_o) const;
        
        
        
        real determinant() const;
        Matrix3 transpose() const;
        Matrix3 cofactor() const;
        void setInverse(const Matrix3 & _m);
        Matrix3 inverse() const;
        void invert();
        
        void dump();
    };
    
    class Matrix4
    {
    public:
        real data[16];
        
        Matrix4();
        Matrix4(    
        real _d0, real _d1, real _d2, real _d3,
        real _d4, real _d5, real _d6, real _d7,
        real _d8, real _d9, real _d10, real _d11,
        real _d12, real _d13, real _d14, real _d15
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
        
        void dump();
        
    };
}
