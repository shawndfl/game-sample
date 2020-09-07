/*
 * Matrix4.h
 *
 *  Created on: Sep 7, 2020
 *      Author: sdady
 */

#ifndef SRC_MATRIX4_H_
#define SRC_MATRIX4_H_

#include "math.h"
#include <ostream>

namespace bsk {

class Matrix4 {
public:
   Matrix4();

   Matrix4(float m11, float m21, float m31, float m41,
           float m12, float m22, float m32, float m42,
           float m13, float m23, float m33, float m43,
           float m14, float m24, float m34, float m44);

   virtual ~Matrix4();

   static const Matrix4 IDENITY;

   union {
      float m[16];
      float mm[4][4];
      struct {
         float m11, m21, m31, m41;
         float m12, m22, m32, m42;
         float m13, m23, m33, m43;
         float m14, m24, m34, m44;
      };
   };

   Matrix4& operator =(const Matrix4& rhs);

   void setUniform(int name);

};

} /* namespace bsk */

std::ostream& operator<<(std::ostream& os, const bsk::Matrix4& mat);

#endif /* SRC_MATRIX4_H_ */
