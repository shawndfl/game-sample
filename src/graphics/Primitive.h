/*
 * Primitive.h
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#ifndef GRAPHICS_QUADPRIMITIVE_H_
#define GRAPHICS_QUADPRIMITIVE_H_

#include "graphics/Geometry.h"
#include <glm/glm.hpp>

namespace bsk {

/**
 * Factory class for creating quads
 */
class Primitive {
public:

   struct posTxtCol {
      glm::vec3 pos;
      glm::vec2 txt;
      glm::vec3 col;
   };

   struct posTxtNorm {
         glm::vec3 pos;
         glm::vec2 txt;
         glm::vec3 norm;
      };

   virtual ~Primitive();

   /**
    * Creates a 3d quad that is from -.5 to .5 in the x and y axis and 0 in the z axis.
    * This quad will have position, texture coordinates and vec3 color. The default color is white
    */
   static Geometry createQuad();

   /**
    * This will create a plane given the normal and position
    */
   static Geometry createPlane(const glm::vec2& size = glm::vec2(1), uint widthSegments = 1, uint horzontalSegments = 1);
private:
   Primitive();

};

} /* namespace bsk */

#endif /* GRAPHICS_QUADPRIMITIVE_H_ */
