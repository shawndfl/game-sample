/*
 * Cube.h
 *
 *  Created on: Mar 29, 2021
 *      Author: sdady
 */

#ifndef SRC_GRAPHICS_CUBE_H_
#define SRC_GRAPHICS_CUBE_H_

#include "graphics/ShaderBlinnPhong.h"
#include "graphics/Camera.h"
#include "graphics/Material.h"
#include "math/Timer.h"

namespace bsk {

class Cube {
public:
   Cube();
   virtual ~Cube();

   void initialize();

   void render(const Camera& camera);

private:

   ShaderBlinnPhong  shader_;
   Texture           diffusedTexture_;
   Geometry          geometry_;

   Material          material_;
   Image             img_;
   Timer             debugTimer_;

   unsigned int shaderProgram;
   unsigned int VAO;
};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_CUBE_H_ */
