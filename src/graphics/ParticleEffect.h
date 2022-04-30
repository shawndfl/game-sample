/*
 * ParticleEffect.h
 *
 *  Created on: Apr 28, 2022
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_PARTICLEEFFECT_H_
#define SRC_GRAPHICS_PARTICLEEFFECT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

namespace bsk {

class ParticleEffect {
public:

   struct EffectParams {
      glm::vec3 startPoint;
      float     lifeTime    = 0;
      glm::vec3 gravity;
      glm::vec3 wind;
      int       maxParticles;
   };

   ParticleEffect();
   virtual ~ParticleEffect();

   /**
    * \brief Creates the particle effect.
    * @param[in] params    The details about how the particles will be created.
    * @param[in] texture   The texture used for rendering the quad.
    * @param[in] u,v       The u,v coordinate of the texture
    */
   void init(const struct EffectParams& params, const Texture& texture, float u, float v);

   /**
    * Render the particles
    * @param[in] dt The time offset in seconds from the last frame.
    */
   void render(float dt);

private:
   struct EffectParams   params_;


};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_PARTICLEEFFECT_H_ */
