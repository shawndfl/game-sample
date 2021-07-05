/*
 * math.h
 *
 *  Created on: Sep 6, 2020
 *      Author: sdady
 */

#ifndef SRC_MATH_H_
#define SRC_MATH_H_

#include <math.h>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4.h"

typedef unsigned int uint;

namespace bsk {
   constexpr double PI = 3.14159265359;
   constexpr double TO_RADIANS = PI/360.0;
   constexpr double TO_DEGREES = 360.0/PI;
}

#endif /* SRC_MATH_H_ */
