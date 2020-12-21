/*
 * math.h
 *
 *  Created on: Sep 6, 2020
 *      Author: sdady
 */

#ifndef SRC_MATH_H_
#define SRC_MATH_H_

#include <math.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix4.h"

namespace bsk {
   constexpr double PI = 3.14159265359;
   constexpr double TO_RADIANS = PI/360.0;
   constexpr double TO_DEGREES = 360.0/PI;
}

#endif /* SRC_MATH_H_ */
