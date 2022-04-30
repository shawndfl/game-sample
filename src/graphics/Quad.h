/*
 * Quad.h
 *
 *  Created on: Apr 28, 2022
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_QUAD_H_
#define SRC_GRAPHICS_QUAD_H_

#include "graphics/Geometry.h"
#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"

namespace bsk {

class Quad {
public:
   Quad();
   virtual ~Quad();

private:
   bsk::Geometry       geometry_;
   bsk::Texture        texture_;
   bsk::ShaderProgram  shader_;
};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_QUAD_H_ */
