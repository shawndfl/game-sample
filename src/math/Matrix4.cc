/*
 * Matrix4.cc
 *
 *  Created on: Sep 7, 2020
 *      Author: sdady
 */

#include "Matrix4.h"
#include <iomanip>
#include "glad/glad.h"

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
void Matrix4::createPerspective(float left, float right, float top, float bottom, float near, float far) {
   const float x = 2.0 * near / (right - left);
   const float y = 2.0 * near / (top - bottom);

   const float a = (right + left) / (right - left);
   const float b = (top + bottom) / (top - bottom);
   const float c = -(far + near) / (far - near);
   const float d = -2.0 * far * near / (far - near);

   m11 = x; m12 = 0;  m13 =  a;  m14 = 0;
   m21 = 0; m22 = y;  m23 =  b;  m24 = 0;
   m31 = 0; m32 = 0;  m33 =  c;  m34 = d;
   m41 = 0; m42 = 0;  m43 = -1.0;  m44 = 0;

}

/*************************************************/
void Matrix4::createOrthographic(float left, float right, float top, float bottom, float near, float far) {
   const float w = 1.0 / ( right - left );
   const float h = 1.0 / ( top - bottom );
   const float p = 1.0 / ( far - near );

   const float x = ( right + left ) * w;
   const float y = ( top + bottom ) * h;
   const float z = ( far + near ) * p;

   m11 = 2.0*w; m12 = 0;    m13 =  0;      m14 = -x;
   m21 = 0;     m22 = 2*h;  m23 =  0;      m24 = -y;
   m21 = 0;     m32 = 0;    m33 =  -2.0*p; m34 = -z;
   m31 = 0;     m42 = 0;    m43 = 0.0;     m44 =  1.0;
}

/*************************************************/
void Matrix4::createProjection(float left, float right, float top, float bottom, float near, float far, float zoom) {
   const float dx = ( right - left ) / ( 2.0   * zoom );
   const float dy = ( top   - bottom ) / ( 2.0 * zoom );
   const float cx = ( right + left ) / 2.0;
   const float cy = ( top   + bottom ) / 2.0;

   float left2 = cx - dx;
   float right2 = cx + dx;
   float top2 = cy + dy;
   float bottom2 = cy - dy;

   createOrthographic(left2, right2, top2, bottom2, near, far);
}

/*************************************************/
void Matrix4::createProjection(float fov, float aspectRatio, float near, float far, float zoom) {
   float angle = fov * TO_RADIANS;
   float top = near * std::tan(angle/2.0) / zoom;
   float height = 2.0 * top;
   float width = aspectRatio * height;
   float left = -.5 * width;

   createPerspective(left, left + width, top, top - height, near, far);
}

/*************************************************/
void Matrix4::createLookAt(const Vector3& eye, const Vector3& target, const Vector3& upAxis) {
   Vector3 lookat = eye - target;
   Vector3 right;
   Vector3 up = upAxis;


   if (lookat.length() == 0) {

      // eye and target are in the same position

      lookat.z = 1.0;

   }

   lookat.normalize();
   right.crossVectors(up, lookat);

   if (right.length() == 0) {

      // up and z are parallel

      if (fabsf(up.z) == 1.0) {

         lookat.x += 0.0001;

      } else {

         lookat.z += 0.0001;

      }

      lookat.normalize();
      right.crossVectors(up, lookat);

   }

   right.normalize();
   up.crossVectors(lookat, right);

   m[ 0 ] = right.x; m[ 4 ] = up.x; m[ 8 ] = lookat.x;
   m[ 1 ] = right.y; m[ 5 ] = up.y; m[ 9 ] = lookat.y;
   m[ 2 ] = right.z; m[ 6 ] = up.z; m[ 10 ] = lookat.z;

}

/*************************************************/
Matrix4 Matrix4::operator *(const Matrix4& rhs) {
   Matrix4 result;
   return Matrix4::multiply(*this, rhs, result);;
}

/*************************************************/
void Matrix4::setUniform(int name) const {
   glUniformMatrix4fv(name, 1, false, m);
}

/*************************************************/
Matrix4& Matrix4::multiply( const Matrix4& a, const Matrix4& b, Matrix4& result ) {

      const float a11 = a.m[ 0 ], a12 = a.m[ 4 ], a13 = a.m[ 8 ], a14 = a.m[ 12 ];
      const float a21 = a.m[ 1 ], a22 = a.m[ 5 ], a23 = a.m[ 9 ], a24 = a.m[ 13 ];
      const float a31 = a.m[ 2 ], a32 = a.m[ 6 ], a33 = a.m[ 10 ], a34 = a.m[ 14 ];
      const float a41 = a.m[ 3 ], a42 = a.m[ 7 ], a43 = a.m[ 11 ], a44 = a.m[ 15 ];

      const float b11 = b.m[ 0 ], b12 = b.m[ 4 ], b13 = b.m[ 8 ], b14 = b.m[ 12 ];
      const float b21 = b.m[ 1 ], b22 = b.m[ 5 ], b23 = b.m[ 9 ], b24 = b.m[ 13 ];
      const float b31 = b.m[ 2 ], b32 = b.m[ 6 ], b33 = b.m[ 10 ], b34 = b.m[ 14 ];
      const float b41 = b.m[ 3 ], b42 = b.m[ 7 ], b43 = b.m[ 11 ], b44 = b.m[ 15 ];

      result.m[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
      result.m[ 4 ] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
      result.m[ 8 ] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
      result.m[ 12 ] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

      result.m[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
      result.m[ 5 ] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
      result.m[ 9 ] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
      result.m[ 13 ] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

      result.m[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
      result.m[ 6 ] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
      result.m[ 10 ] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
      result.m[ 14 ] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

      result.m[ 3 ] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
      result.m[ 7 ] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
      result.m[ 11 ] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
      result.m[ 15 ] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

      return result;

   }


} /* namespace bsk */

/*************************************************/
std::ostream& operator<<(std::ostream& os, const bsk::Matrix4& mat) {
   os << "\n"
      << std::setw(10) << mat.m11 << ", " << std::setw(10) << mat.m21 << ", " << std::setw(10) << mat.m31 << ", " << std::setw(10) << mat.m41 << "\n"
      << std::setw(10) << mat.m12 << ", " << std::setw(10) << mat.m22 << ", " << std::setw(10) << mat.m32 << ", " << std::setw(10) << mat.m42 << "\n"
      << std::setw(10) << mat.m13 << ", " << std::setw(10) << mat.m23 << ", " << std::setw(10) << mat.m33 << ", " << std::setw(10) << mat.m43 << "\n"
      << std::setw(10) << mat.m14 << ", " << std::setw(10) << mat.m24 << ", " << std::setw(10) << mat.m34 << ", " << std::setw(10) << mat.m44;
   return os;
}
