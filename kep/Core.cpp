#include "Core.h"
using namespace Kep;
void Vector3::operator *=(const real _value)
{
    m_x *= _value;
    m_y *= _value;
    m_z *= _value;
}
Vector3 Vector3::operator *(const real _value)
{
    return Vector3(m_x*_value, m_y*_value, m_z*_value);
}
        
void Vector3::operator +=(const Vector3 & _v)
{
    m_x += _v.m_x;
    m_y += _v.m_y;
    m_z += _v.m_z;
}
Vector3 Vector3::operator +(const Vector3 & _v)
{
    return Vector3(m_x + _v.m_x, m_y + _v.m_y, m_z + _v.m_z);
}

void Vector3::operator -=(const Vector3 & _v)
{
    m_x -= _v.m_x;
    m_y -= _v.m_y;
    m_z -= _v.m_z;
}
Vector3 Vector3::operator -(const Vector3 & _v)
{
    return Vector3(m_x - _v.m_x, m_y - _v.m_y, m_z - _v.m_z);
}


void Vector3::invert()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

real Vector3::magnitude()
{
    return sqrt( m_x*m_x + m_y*m_y + m_z*m_z);
}

real Vector3::squareMagnitude()
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

Vector3 Vector3::componentProduct(const Vector3 & _vector)
{
    return Vector3 (m_x * _vector.m_x, m_y * _vector.m_y, m_z * _vector.m_z );
}

real Vector3::scalarProduct(const Vector3 & _vector)
{
    return m_x*_vector.m_x + m_y*_vector.m_y + m_x*_vector.m_z;
}
real Vector3::operator * (const Vector3 & _vector)
{
    return m_x*_vector.m_x + m_y*_vector.m_y + m_z*_vector.m_z;
}

Vector3 Vector3::vectorProduct(const Vector3 & _vector)
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
Vector3 Vector3::operator %(const Vector3 & _vector)

{
    return Vector3(m_y*_vector.m_z - m_z*_vector.m_y,
                    m_z*_vector.m_x - m_x*_vector.m_z,
                    m_x*_vector.m_y - m_y*_vector.m_x);
}

void Vector3::dump()
{
    printf("x: %f, y: %f, z: %f \n", m_x, m_y, m_z );
}






Matrix3::~Matrix3()
{}

Matrix3::Matrix3(    
    real _d0, real _d1, real _d2,
    real _d3, real _d4, real _d5,
    real _d6, real _d7, real _d8
    )
{
    data[0] = _d0; data[1] = _d1; data[2] = _d2; 
    data[3] = _d3; data[4] = _d4; data[5] = _d5; 
    data[6] = _d6; data[7] = _d7; data[8] = _d8;
}

Matrix3 Matrix3::operator*(const Matrix3 &_o) const
{
//     return Matrix3(
//         data[0]*_o.data[0] + data[1]*_o.data[3] + data[2]*_o.data[6],
//         data[0]*_o.data[1] + data[1]*_o.data[4] + data[2]*_o.data[7],
//         data[0]*_o.data[2] + data[1]*_o.data[5] + data[2]*_o.data[8],
//         
//         data[3]*_o.data[0] + data[4]*_o.data[3] + data[5]*_o.data[6],
//         data[3]*_o.data[1] + data[4]*_o.data[4] + data[5]*_o.data[7],
//         data[3]*_o.data[2] + data[4]*_o.data[5] + data[5]*_o.data[8],
//         
//         data[6]*_o.data[0] + data[7]*_o.data[3] + data[8]*_o.data[6],
//         data[6]*_o.data[1] + data[7]*_o.data[4] + data[8]*_o.data[7],
//         data[6]*_o.data[2] + data[7]*_o.data[5] + data[8]*_o.data[8]
//     );
    Matrix3 result;
    result.data[0] = data[0]*_o.data[0]  + data[1]*_o.data[3] + data[2]*_o.data[6];
    result.data[1] = data[0]*_o.data[1]  + data[1]*_o.data[4] + data[2]*_o.data[7];
    result.data[2] = data[0]*_o.data[2]  + data[1]*_o.data[5] + data[2]*_o.data[8];
    
    
    result.data[3] = data[3]*_o.data[0]  + data[4]*_o.data[3] + data[5]*_o.data[6];
    result.data[4] = data[3]*_o.data[1]  + data[4]*_o.data[4] + data[5]*_o.data[7];
    result.data[5] = data[3]*_o.data[2]  + data[4]*_o.data[5] + data[5]*_o.data[8];
    
    result.data[6] = data[6]*_o.data[0]  + data[7]*_o.data[3] + data[8]*_o.data[6];
    result.data[7] = data[6]*_o.data[1]  + data[7]*_o.data[4] + data[8]*_o.data[7];
    result.data[8] = data[6]*_o.data[2]  + data[7]*_o.data[5] + data[8]*_o.data[8];
    return result;
}

real Matrix3::determinant() const
{
//     return (
//         data[0]*data[4]*data[8] +
//         data[1]*data[5]*data[6] +
//         data[2]*data[5]*data[7] -
//         
//         data[2]*data[4]*data[6] -
//         data[1]*data[3]*data[8] -
//         data[0]*data[5]*data[7]
//     );
    return 
    (data[0]*((data[4]*data[8]) - (data[7]*data[5]))
    -data[1]*((data[3]*data[8]) - (data[5]*data[6]))
    +data[2]*((data[3]*data[7]) - (data[6]*data[4])));
}

Matrix3 Matrix3::transpose() const
{
    return Matrix3(
        data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8]
    );
}

Matrix3 Matrix3::cofactor() const
{
    Matrix3 m;
    m.data[0] =   ((data[4]*data[8]) - (data[7]*data[5]));
    m.data[1] = - ((data[3]*data[8]) - (data[5]*data[6]));
    m.data[2] =   ((data[3]*data[7]) - (data[6]*data[4]));
    m.data[3] = - ((data[1]*data[8]) - (data[2]*data[7]));
    m.data[4] =   ((data[0]*data[8]) - (data[2]*data[6]));
    m.data[5] = - ((data[0]*data[7]) - (data[1]*data[6]));
    m.data[6] =   ((data[1]*data[5]) - (data[2]*data[4]));
    m.data[7] = - ((data[0]*data[5]) - (data[2]*data[3]));
    m.data[8] =   ((data[0]*data[4]) - (data[1]*data[3]));
    
    return m;
}

void Matrix3::setInverse(const Matrix3 & _m)
{
    real det = _m.determinant();
    if(det == 0) return;
    
    real invDet = 1.0f/det;
    
    Matrix3 cof = _m.cofactor();
    Matrix3 cofTrans = cof.transpose();
    
    data[0] = invDet * cofTrans.data[0]; 
    data[1] = invDet * cofTrans.data[1];
    data[2] = invDet * cofTrans.data[2];
    data[3] = invDet * cofTrans.data[3];
    data[4] = invDet * cofTrans.data[4];
    data[5] = invDet * cofTrans.data[5];
    data[6] = invDet * cofTrans.data[6];
    data[7] = invDet * cofTrans.data[7];
    data[8] = invDet * cofTrans.data[8];
}

Matrix3 Matrix3::inverse() const
{
    Matrix3 result;
    result.setInverse(*this);
    return result;
}

void Matrix3::invert()
{
    setInverse(*this);
}
void Matrix3::setOrientation(const Quaternion &_q)
{
    data[0] = 1 - (2*_q.j*_q.j + 2*_q.k*_q.k);
    
    data[1] = 2*_q.i*_q.j + 2*_q.k*_q.r;
    data[2] = 2*_q.i*_q.k + 2*_q.j*_q.r;
    data[3] = 2*_q.i*_q.j + 2*_q.k*_q.r;
    
    data[4] = 1 - (2*_q.i*_q.i + 2*_q.k*_q.k);
    
    data[5] = 2*_q.j*_q.k + 2*_q.i*_q.r;
    data[6] = 2*_q.i*_q.k + 2*_q.j*_q.r;
    data[7] = 2*_q.j*_q.k + 2*_q.i*_q.r;
    
    data[8] = 1 - (2*_q.i*_q.i + 2*_q.j*_q.j);
}

void Matrix3::dump()
{
    printf("%f %f %f \n%f %f %f \n%f %f %f",
           data[0], data[1], data[2],
           data[3], data[4], data[5],
           data[6], data[7], data[8]
    );
}
                 
                 
                 

Matrix4::Matrix4(
    real _d0, real _d1, real _d2, real _d3,
    real _d4, real _d5, real _d6, real _d7,
    real _d8, real _d9, real _d10, real _d11,
    real _d12, real _d13, real _d14, real _d15
    
)
{
    data[0] = _d0; data[1] = _d1; data[2] = _d2; data[3] = _d3;
    data[4] = _d4; data[5] = _d5; data[6] = _d6; data[7] = _d7;
    data[8] = _d8; data[9] = _d9; data[10] = _d10; data[11] = _d11;
    data[12] = _d12; data[13] = _d13; data[14] = _d14; data[15] = _d15;
}
Matrix4::~Matrix4()
{
    
}
Vector3 Matrix4::operator*(const Vector3 & _vector) const
{
    return Vector3(data[0]*_vector.m_x + data[1]*_vector.m_y + data[2]*_vector.m_z + data[3], 
                   data[4]*_vector.m_x + data[5]*_vector.m_y + data[6]*_vector.m_z + data[7],
                   data[8]*_vector.m_x + data[9]*_vector.m_y + data[10]*_vector.m_z + data[11]);
}

Matrix4 Matrix4::operator*(const Matrix4 &_o) const
{
    Matrix4 result;
    result.data[0] = data[0]*_o.data[0]  + data[1]*_o.data[4] + data[2]*_o.data[8] + data[3]*_o.data[12];
    result.data[1] = data[0]*_o.data[1]  + data[1]*_o.data[5] + data[2]*_o.data[9] + data[3]*_o.data[13];
    result.data[2] = data[0]*_o.data[2]  + data[1]*_o.data[6] + data[2]*_o.data[10] + data[3]*_o.data[14];
    result.data[3] = data[0]*_o.data[3]  + data[1]*_o.data[7] + data[2]*_o.data[11] + data[3]*_o.data[15];
    
    result.data[4] = data[4]*_o.data[0]  + data[5]*_o.data[4] + data[6]*_o.data[8] + data[7]*_o.data[12];
    result.data[5] = data[4]*_o.data[1]  + data[5]*_o.data[5] + data[6]*_o.data[9] + data[7]*_o.data[13];
    result.data[6] = data[4]*_o.data[2]  + data[5]*_o.data[6] + data[6]*_o.data[10] + data[7]*_o.data[14];
    result.data[7] = data[4]*_o.data[3]  + data[5]*_o.data[7] + data[6]*_o.data[11] + data[7]*_o.data[15];
    
    result.data[8] = data[8]*_o.data[0]  + data[9]*_o.data[4] + data[10]*_o.data[8] + data[11]*_o.data[12];
    result.data[9] = data[8]*_o.data[1]  + data[9]*_o.data[5] + data[10]*_o.data[9] + data[11]*_o.data[13];
    result.data[10] = data[8]*_o.data[2]  + data[9]*_o.data[6] + data[10]*_o.data[10] + data[11]*_o.data[14];
    result.data[11] = data[8]*_o.data[3]  + data[9]*_o.data[7] + data[10]*_o.data[11] + data[11]*_o.data[15];
    
    result.data[12] = data[12]*_o.data[0]  + data[13]*_o.data[4] + data[14]*_o.data[8] + data[15]*_o.data[12];
    result.data[13] = data[12]*_o.data[1]  + data[13]*_o.data[5] + data[14]*_o.data[9] + data[15]*_o.data[13];
    result.data[14] = data[12]*_o.data[2]  + data[13]*_o.data[6] + data[14]*_o.data[10] + data[15]*_o.data[14];
    result.data[15] = data[12]*_o.data[3]  + data[13]*_o.data[7] + data[14]*_o.data[11] + data[15]*_o.data[15];
    
    return result;
}

Matrix4 Matrix4:: inverse() const
{
    Matrix4 result;
    result.setInverse(*this);
    return result;
}

void Matrix4::invert()
{
    setInverse(*this);
}

real Matrix4::determinant() const
{
    Matrix3 m[4];
    
    m[0] = Matrix3(
        data[5], data[6], data[7],
        data[9], data[10], data[11],
        data[13], data[14], data[15]
    );
    
    m[1] = Matrix3(
        data[4], data[6], data[7],
        data[8], data[10], data[11],
        data[12], data[14], data[15]
    );
    
    m[2] = Matrix3(
        data[4], data[5], data[7],
        data[8], data[9], data[11],
        data[12], data[13], data[15]
    );
    m[3] = Matrix3(
        data[4], data[5], data[6],
        data[8], data[9], data[10],
        data[12], data[13], data[14]
    );
    
    return ((data[0]*m[0].determinant()) - (data[1]*m[1].determinant()) + (data[2]*m[2].determinant()) - (data[3]*m[3].determinant()));
}
Matrix4 Matrix4::transpose() const
{
    return Matrix4(
        data[0], data[4], data[8], data[12],
        data[1], data[5], data[9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15]
    );
}
Matrix4 Matrix4::cofactor() const
{
    Matrix3 m[16];
    m[0] = Matrix3(
        data[5], data[6], data[7],
        data[9], data[10], data[11],
        data[13], data[14], data[15]
    );
    
    m[1] = Matrix3(
        data[4], data[6], data[7],
        data[8], data[10], data[11],
        data[12], data[14], data[15]
    );
    
    m[2] = Matrix3(
        data[4], data[5], data[7],
        data[8], data[9], data[11],
        data[12], data[13], data[15]
    );
    m[3] = Matrix3(
        data[4], data[5], data[6],
        data[8], data[9], data[10],
        data[12], data[13], data[14]
    );
    
    
    
    m[4] = Matrix3(
        data[1], data[2], data[3],
        data[9], data[10], data[11],
        data[13], data[14], data[15]
    );
    m[5] = Matrix3(
        data[0], data[2], data[3],
        data[8], data[10], data[11],
        data[12], data[14], data[15]
    );
    m[6] = Matrix3(
        data[0], data[1], data[3],
        data[8], data[9], data[11],
        data[12], data[13], data[15]
    );
    m[7] = Matrix3(
        data[0], data[1], data[2],
        data[8], data[9], data[10],
        data[12], data[13], data[14]
    );
    
    
    
    m[8] = Matrix3(
        data[1], data[2], data[3],
        data[5], data[6], data[7],
        data[13], data[14], data[15]
    );
    m[9] = Matrix3(
        data[0], data[2], data[3],
        data[4], data[6], data[7],
        data[12], data[14], data[15]
    );
    m[10] = Matrix3(
        data[0], data[1], data[3],
        data[4], data[5], data[7],
        data[12], data[13], data[15]
    );
    m[11] = Matrix3(
        data[0], data[1], data[2],
        data[4], data[5], data[6],
        data[12], data[13], data[14]
    );
    
    
    m[12] = Matrix3(
        data[1], data[2], data[3],
        data[5], data[6], data[7],
        data[9], data[10], data[11]
    );
    m[13] = Matrix3(
        data[0], data[2], data[3],
        data[4], data[6], data[7],
        data[8], data[10], data[11]
    );
    m[14] = Matrix3(
        data[0], data[1], data[3],
        data[4], data[5], data[7],
        data[8], data[9], data[11]
    );
    m[15] = Matrix3(
        data[0], data[1], data[2],
        data[4], data[5], data[6],
        data[8], data[9], data[10]
    );
    
    return Matrix4(
        m[0].determinant(), -m[1].determinant(), m[2].determinant(), -m[3].determinant(),
        -m[4].determinant(), m[5].determinant(), -m[6].determinant(), m[7].determinant(),
        m[8].determinant(), -m[9].determinant(), m[10].determinant(), -m[11].determinant(),
        -m[12].determinant(), m[13].determinant(), -m[14].determinant(), m[15].determinant()
    );
}
void Matrix4::setInverse(const Matrix4 &_m)
{
    real det = _m.determinant();
    if(det == 0) return;
    real invDet = 1.0f/det;
    
    Matrix4 cof = _m.cofactor();
    Matrix4 cofTrans = cof.transpose();
    
    data[0] = invDet * cofTrans.data[0]; 
    data[1] = invDet * cofTrans.data[1];
    data[2] = invDet * cofTrans.data[2];
    data[3] = invDet * cofTrans.data[3];
    data[4] = invDet * cofTrans.data[4];
    data[5] = invDet * cofTrans.data[5];
    data[6] = invDet * cofTrans.data[6];
    data[7] = invDet * cofTrans.data[7];
    data[8] = invDet * cofTrans.data[8];
    
    data[9] = invDet * cofTrans.data[9]; 
    data[10] = invDet * cofTrans.data[10];
    data[11] = invDet * cofTrans.data[11];
    data[12] = invDet * cofTrans.data[12];
    data[13] = invDet * cofTrans.data[13];
    data[14] = invDet * cofTrans.data[14];
    data[15] = invDet * cofTrans.data[15];
    
}

void Matrix4::setOrientationAndPos(const Quaternion &_q, const Vector3 &_pos)
{
    data[0] = 1 - (2*_q.j*_q.j + 2*_q.k*_q.k);
    data[1] = 2*_q.i*_q.j + 2*_q.k*_q.r;
    data[2] = 2*_q.i*_q.k - 2*_q.j*_q.r;
    data[3] = _pos.m_x;
    
    data[4] = (2*_q.i*_q.j - 2*_q.k*_q.r);
    data[5] = 1 - (2*_q.i*_q.i + 2*_q.k*_q.k);
    data[6] = 2*_q.j*_q.k + 2*_q.i*_q.r;
    data[7] = _pos.m_y;
    
    data[8] = 2*_q.i*_q.k + 2*_q.j*_q.r;
    data[9] = 2*_q.j*_q.k + 2*_q.i*_q.r;
    data[10] = 1 - (2*_q.i*_q.i + 2*_q.j*_q.j);
    data[11] = _pos.m_z;
}

void Matrix4::dump()
{
        printf("%.2f %.2f %.2f %.2f \n%.2f %.2f %.2f %.2f \n%.2f %.2f %.2f %.2f \n%.2f %.2f %.2f %.2f",
           data[0], data[1], data[2],  data[3], 
           data[4], data[5], data[6],  data[7],
           data[8], data[9], data[10], data[11],
           data[12], data[13], data[14], data[15]           
    );
}


