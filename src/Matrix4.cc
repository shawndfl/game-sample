/*
 * Matrix4.cc
 *
 *  Created on: Sep 7, 2020
 *      Author: sdady
 */

#include "Matrix4.h"
#include <GLES2/gl2.h>

namespace bsk {

const Matrix4 Matrix4::IDENITY(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1);

/*************************************************/
Matrix4::Matrix4() {
   operator =(IDENITY);
}

/*************************************************/
Matrix4::~Matrix4() {

}

/*************************************************/
Matrix4::Matrix4(
      float m11, float m21, float m31, float m41,
      float m12, float m22, float m32, float m42,
      float m13, float m23, float m33, float m43,
      float m14, float m24, float m34, float m44) {

  m[0] = m11; m[4] = m21; m[8]  = m31; m[12] = m41;
  m[1] = m12; m[5] = m22; m[9]  = m32; m[13] = m42;
  m[2] = m13; m[6] = m23; m[10] = m33; m[14] = m43;
  m[3] = m14; m[7] = m24; m[11] = m34; m[15] = m44;
}

/*************************************************/
Matrix4& Matrix4::operator =(const Matrix4 &rhs) {
   m[0] = rhs.m[0]; m[4] = rhs.m[4]; m[8]  = rhs.m[8];  m[12] = rhs.m[12];
   m[1] = rhs.m[1]; m[5] = rhs.m[5]; m[9]  = rhs.m[9];  m[13] = rhs.m[13];
   m[2] = rhs.m[2]; m[6] = rhs.m[6]; m[10] = rhs.m[10]; m[14] = rhs.m[14];
   m[3] = rhs.m[3]; m[7] = rhs.m[7]; m[11] = rhs.m[11]; m[15] = rhs.m[15];
   return *this;
}

/*************************************************/
void Matrix4::setTranslation(const Vector3& position) {
   m14 = position.x;
   m24 = position.y;
   m34 = position.z;
}

/*************************************************/
void Matrix4::setTranslation(float x, float y, float z) {
   m14 = x;
   m24 = y;
   m34 = z;
}

/*************************************************/
Vector3 Matrix4::getTranslation() {
   Vector3 pos(m14, m24, m34);
   return pos;
}

/*************************************************/
Matrix4& Matrix4::transpose() {


   float tmp;

   tmp = m[ 1 ]; m[ 1 ] = m[ 4 ]; m[ 4 ] = tmp;
   tmp = m[ 2 ]; m[ 2 ] = m[ 8 ]; m[ 8 ] = tmp;
   tmp = m[ 6 ]; m[ 6 ] = m[ 9 ]; m[ 9 ] = tmp;

   tmp = m[ 3 ]; m[ 3 ] = m[ 12 ]; m[ 12 ] = tmp;
   tmp = m[ 7 ]; m[ 7 ] = m[ 13 ]; m[ 13 ] = tmp;
   tmp = m[ 11 ]; m[ 11 ] = m[ 14 ]; m[ 14 ] = tmp;

   return *this;
}

/*************************************************/
void Matrix4::setUniform(int name) const {
   glUniformMatrix4fv(name, 1, false, m);
}


} /* namespace bsk */

/*************************************************/
std::ostream& operator<<(std::ostream& os, const bsk::Matrix4& mat) {
   os << "\n   "
      << mat.m11 << ", " << mat.m21 << ", " << mat.m31 << ", " << mat.m41 << "\n   "
      << mat.m12 << ", " << mat.m22 << ", " << mat.m32 << ", " << mat.m42 << "\n   "
      << mat.m13 << ", " << mat.m23 << ", " << mat.m33 << ", " << mat.m43 << "\n   "
      << mat.m14 << ", " << mat.m24 << ", " << mat.m34 << ", " << mat.m44;
   return os;
}
