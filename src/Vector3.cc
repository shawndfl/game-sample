/*
 * Vector3.cc
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#include "Vector3.h"
#include <GLES2/gl2.h>

namespace bsk {


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


} /* namespace bsk */
