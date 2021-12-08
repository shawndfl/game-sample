/*
 * math.h
 *
 *  Created on: Sep 6, 2020
 *      Author: sdady
 */
#include "math/Math.h"
#include <iomanip>

/*************************************************/
std::ostream& operator<<(std::ostream& os, const glm::mat4x4& mat) {
   os << "\n"
      << std::setw(10) << mat[0][0] << ", " << std::setw(10) << mat[1][0] << ", " << std::setw(10) << mat[2][0] << ", " << std::setw(10) << mat[3][0] << "\n"
      << std::setw(10) << mat[0][1] << ", " << std::setw(10) << mat[1][1] << ", " << std::setw(10) << mat[2][1] << ", " << std::setw(10) << mat[3][1] << "\n"
      << std::setw(10) << mat[0][2] << ", " << std::setw(10) << mat[1][2] << ", " << std::setw(10) << mat[2][2] << ", " << std::setw(10) << mat[3][2] << "\n"
      << std::setw(10) << mat[0][3] << ", " << std::setw(10) << mat[1][3] << ", " << std::setw(10) << mat[2][3] << ", " << std::setw(10) << mat[3][3];
   return os;
}

/*************************************************/
std::ostream& operator<<(std::ostream& os, const glm::vec2& vec) {
   os << "\n"
      << std::setw(10) << vec.x << ", " << std::setw(10) << vec.y;
   return os;
}

/*************************************************/
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
   os << "\n"
      << std::setw(10) << vec.x << ", " << std::setw(10) << vec.y << ", " << std::setw(10) << vec.z;
   return os;
}

/*************************************************/
std::ostream& operator<<(std::ostream& os, const glm::vec4& vec) {
   os << "\n"
      << std::setw(10) << vec.x << ", " << std::setw(10) << vec.y << ", " << std::setw(10) << vec.z << ", " << std::setw(10) << vec.w;
   return os;
}

