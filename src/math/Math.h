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

#include "glm/glm.hpp"
#include "glm/ext.hpp"

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
}

std::ostream& operator<<(std::ostream& os, const glm::mat4x4& mat);

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec4& vec);

#endif /* SRC_MATH_CORE_H_ */
