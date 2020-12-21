/*
 * Vector3.cc
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#include "Vector3.h"
#include "Matrix4.h"
#include <GLES2/gl2.h>
#include <math.h>
#include <iomanip>

namespace bsk {


const Vector3 Vector3::ONE(1,1,1);
const Vector3 Vector3::ZERO(0,0,0);
const Vector3 Vector3::UP(0,1,0);
const Vector3 Vector3::DOWN(0,-1,0);
const Vector3 Vector3::RIGHT(1,0,0);
const Vector3 Vector3::LEFT(-1,0,0);
const Vector3 Vector3::FORWARD(0,0,1);
const Vector3 Vector3::BACKWARDS(0,0,-1);

/*************************************************/
Vector3::Vector3(): x(0), y(0), z(0) {

}

/*************************************************/
Vector3::~Vector3() {

}

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {
}

/*************************************************/
void Vector3::setUniform(int name) {
   glUniform3f(name, x, y, z);
}

/*************************************************/
Vector3 Vector3::operator -(const Vector3& rhs) {
   Vector3 result(x - rhs.x, y - rhs.y, z - rhs.z);
   return result;
}

/*************************************************/
float Vector3::length() const {
   return sqrt(x*x + y*y + z*z);
}

/*************************************************/
Vector3& Vector3::normalize() {
   float len = (length() == 0.0) ? 1.0: length();
   return operator /(len);
}

/*************************************************/
Vector3& Vector3::operator /(float scalar) {
   return operator *(1.0 / scalar);
}

/*************************************************/
Vector3& Vector3::operator *(float scalar) {
   x *= scalar;
   y *= scalar;
   z *= scalar;
   return *this;
}

/*************************************************/
Vector3& Vector3::operator +(const Vector3& rhs) {\
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;
   return *this;
}

/*************************************************/
Vector3& Vector3::cross(const Vector3& axis) {

   return crossVectors(*this, axis);
}

/*************************************************/
Vector3& Vector3::transform(const Matrix4& mat) {
   Vector3 transform;
   const float x = this->x;
   const float y = this->y;
   const float z = this->z;

   this->x = mat.m11 * x + mat.m12 * y + mat.m13 * z + mat.m14;
   this->y = mat.m21 * x + mat.m22 * y + mat.m23 * z + mat.m24;
   this->z = mat.m31 * x + mat.m32 * y + mat.m33 * z + mat.m34;
   return *this;

}

/*************************************************/
Vector3& Vector3::crossVectors(const Vector3& a, const Vector3& b) {
   const float ax = a.x, ay = a.y, az = a.z;
   const float bx = b.x, by = b.y, bz = b.z;

   x = ay * bz - az * by;
   y = az * bx - ax * bz;
   z = ax * by - ay * bx;
   return *this;
}

} /* namespace bsk */

/*************************************************/
bsk::Vector3 operator-(const bsk::Vector3& lhs, const bsk::Vector3& rhs) {
   bsk::Vector3 result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z- rhs.z);
   return result;

}

/*************************************************/
std::ostream& operator<<(std::ostream& os, const bsk::Vector3& vec) {
   os << "[" << std::setw(10) << vec.x << ", " << std::setw(10) << vec.y << ", " << std::setw(10) << vec.z << "]";
   return os;
}
