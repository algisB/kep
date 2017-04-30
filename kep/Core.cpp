#include "Core.h"
using namespace Kep;
void Vector3::operator *=(const real _value)
{
    m_x *= _value;
    m_y *= _value;
    m_z *= _value;
}
const Vector3 Vector3::operator *(const real _value)
{
    return Vector3(m_x*_value, m_y*_value, m_z*_value);
}
        
void Vector3::operator +=(const Vector3 & _v)
{
    m_x += _v.m_x;
    m_y += _v.m_y;
    m_z += _v.m_z;
}
const Vector3 Vector3::operator +(const Vector3 & _v)
{
    return Vector3(m_x + _v.m_x, m_y + _v.m_y, m_z + _v.m_z);
}

void Vector3::operator -=(const Vector3 & _v)
{
    m_x -= _v.m_x;
    m_y -= _v.m_y;
    m_z -= _v.m_z;
}
const Vector3 Vector3::operator -(const Vector3 & _v)
{
    return Vector3(m_x - _v.m_x, m_y - _v.m_y, m_z - _v.m_z);
}


void Vector3::invert()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

const real Vector3::magnitude()
{
    return sqrt( m_x*m_x + m_y*m_y + m_z*m_z);
}

const real Vector3::squareMagnitude()
{
    return m_x*m_x + m_y*m_y + m_z*m_z;
}
void Vector3::normalize()
{
    real m = magnitude();
    if(m > 0)
    {
        (*this) *= ((real)1)/m;
    }
}

void Vector3::addScaledVector(const Vector3 & _vector, const real _scale)
{
    m_x += _vector.m_x * _scale;
    m_y += _vector.m_y * _scale;
    m_z += _vector.m_z * _scale;
}

const Vector3 Vector3::componentProduct(const Vector3 & _vector)
{
    return Vector3 (m_x * _vector.m_x, m_y * _vector.m_y, m_z * _vector.m_z );
}

const real Vector3::scalarProduct(const Vector3 & _vector)
{
    return m_x*_vector.m_x + m_y*_vector.m_y + m_x*_vector.m_z;
}
const real Vector3::operator * (const Vector3 & _vector)
{
    return m_x*_vector.m_x + m_y*_vector.m_y + m_z*_vector.m_z;
}

const Vector3 Vector3::vectorProduct(const Vector3 & _vector)
{
    return Vector3(
        m_y*_vector.m_z - m_z*_vector.m_y,
        m_z*_vector.m_x - m_x*_vector.m_z,
        m_x*_vector.m_y - m_y*_vector.m_x
    );
}

void Vector3::operator %=(const Vector3 & _vector)
{
    *this = vectorProduct(_vector);
}
const Vector3 Vector3::operator %(const Vector3 & _vector)
{
    return Vector3(m_y*_vector.m_z - m_z*_vector.m_y,
                    m_z*_vector.m_x - m_x*_vector.m_z,
                    m_x*_vector.m_y - m_y*_vector.m_x);
}

void Vector3::dump()
{
    printf("x: %f, y: %f, z: %f \n", m_x, m_y, m_z );
}
