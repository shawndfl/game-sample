/*
 * Particle.h
 *
 *  Created on: Apr 28, 2022
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_PARTICLE_H_
#define SRC_GRAPHICS_PARTICLE_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace bsk {
/**
 * A particle, which is a quad that gets rendered
 */
class Particle {
public:
   Particle();
   virtual ~Particle();

private:
   glm::vec4 color_;
   glm::vec3 pos_;
   float     lifeTime_;
   glm::vec2 scale_;
};

}

#endif /* SRC_GRAPHICS_PARTICLE_H_ */
