/*
 * Ground.h
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#ifndef MESHES_GROUND_H_
#define MESHES_GROUND_H_

#include "graphics/Geometry.h"
#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"
#include "core/Camera.h"
#include "core/Object3D.h"

namespace bsk {

class Ground: public Object3d {
public:
   Ground();
   virtual ~Ground();

   void initialize();

   void render(const Camera& camera);
private:
   bsk::Geometry       geometry_;
   bsk::Texture        texture_;
   bsk::ShaderProgram  shader_;

   bool initialized_;
};

} /* namespace bsk */

#endif /* MESHES_GROUND_H_ */
