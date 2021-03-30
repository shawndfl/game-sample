/*
 * Cube.h
 *
 *  Created on: Mar 29, 2021
 *      Author: sdady
 */

#ifndef SRC_GRAPHICS_CUBE_H_
#define SRC_GRAPHICS_CUBE_H_

#include "graphics/ShaderBlinnPhong.h"

namespace bsk {

class Cube {
public:
   Cube();
   virtual ~Cube();

   void initialize();

   void render();

private:

   ShaderBlinnPhong  shader_;
   Texture           diffusedTexture_;
   Geometry          geometry_;
   Matrix4           transform_;
};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_CUBE_H_ */
