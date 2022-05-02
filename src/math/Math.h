/*
 * math.h
 *
 *  Created on: Sep 6, 2020
 *      Author: sdady
 */

#ifndef SRC_MATH_CORE_H_
#define SRC_MATH_CORE_H_

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bsk {
    typedef float Milliseconds;

    constexpr glm::vec3 vec3Zero     = glm::vec3(0,0,0);
    constexpr glm::vec3 vec3One      = glm::vec3(1,1,1);
    constexpr glm::vec3 vec3Up       = glm::vec3(0,1,0);
    constexpr glm::vec3 vec3Down     = glm::vec3(0,-1,0);
    constexpr glm::vec3 vec3Right    = glm::vec3(1,0,0);
    constexpr glm::vec3 vec3Left     = glm::vec3(-1,0,0);
    constexpr glm::vec3 vec3Forward  = glm::vec3(0,0,1);
    constexpr glm::vec3 vec3Back     = glm::vec3(0,0,-1);

    inline glm::mat4 compose(const glm::vec3& pos, const glm::quat& rotation, const glm::vec3 scale);
}

std::ostream& operator<<(std::ostream& os, const glm::mat4x4& mat);

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec4& vec);

/*************************************************/
glm::mat4 bsk::compose(const glm::vec3& pos, const glm::quat& rotation, const glm::vec3 scale) {
   glm::mat4 mat;

   float x = rotation.x;
   float y = rotation.y;
   float z = rotation.z;
   float w = rotation.w;

   float x2 = x + x, y2 = y + y, z2 = z + z;
   float xx = x * x2, xy = x * y2, xz = x * z2;
   float yy = y * y2, yz = y * z2, zz = z * z2;
   float wx = w * x2, wy = w * y2, wz = w * z2;

   float sx = scale.x;
   float sy = scale.y;
   float sz = scale.z;

   mat[0].x = (1 - (yy + zz)) * sx;
   mat[1].x = (xy + wz) * sx;
   mat[2].x = (xz - wy) * sx;
   mat[3].x = 0;

   mat[0].y = (xy - wz) * sy;
   mat[1].y = (1 - (xx + zz)) * sy;
   mat[2].y = (yz + wx) * sy;
   mat[3].y = 0;

   mat[0].z= (xz + wy) * sz;
   mat[1].z= (yz - wx) * sz;
   mat[2].z = (1 - (xx + yy)) * sz;
   mat[3].z = 0;

   mat[0].w = pos.x;
   mat[1].w = pos.y;
   mat[2].w = pos.z;
   mat[3].w = 1;
   /*
   mat[0].x = (1 - (yy + zz)) * sx;
   mat[0].y = (xy + wz) * sx;
   mat[0].z = (xz - wy) * sx;
   mat[0].w = 0;

   mat[1].x = (xy - wz) * sy;
   mat[1].y = (1 - (xx + zz)) * sy;
   mat[1].z = (yz + wx) * sy;
   mat[1].w = 0;

   mat[2].x = (xz + wy) * sz;
   mat[2].y = (yz - wx) * sz;
   mat[2].z = (1 - (xx + yy)) * sz;
   mat[2].w = 0;

   mat[3].x = pos.x;
   mat[3].y = pos.y;
   mat[3].z = pos.z;
   mat[3].w = 1;
   */
   return mat;
}

#endif /* SRC_MATH_CORE_H_ */
