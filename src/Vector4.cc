/*
 * Vector4.cc
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#include "Vector4.h"
#include <GLES2/gl2.h>

namespace bsk {

Vector4 Vector4::ONE(1,1,1,1);
Vector4 Vector4::ZERO(0,0,0,0);

/*************************************************/
Vector4::Vector4() {
   this->x = 0;
   this->y = 0;
   this->z = 0;
   this->w = 1.0;
}

/*************************************************/
Vector4::Vector4(float x, float y, float z, float w) {

   this->x = x;
   this->y = y;
   this->z = z;
   this->w = w;
}

/*************************************************/
void Vector4::setUniform(int name) {
   glUniform4f(name, x, y, z, w);
}

/*************************************************/
Vector4::~Vector4() {
   // TODO Auto-generated destructor stub
}

} /* namespace bsk */
