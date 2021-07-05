/*
 * Vector2.cc
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#include "Vector2.h"
#include "glad/glad.h"

namespace bsk {

/*************************************************/
Vector2::Vector2(): x(0), y(0) {

}

/*************************************************/
Vector2::Vector2(float x, float y) {
   this->x = x;
   this->y = y;
}

/*************************************************/
Vector2::~Vector2() {
}

/*************************************************/
void Vector2::setUniform(int name) const {
   glUniform2f(name, x, y);
}

} /* namespace bsk */
