/*
 * Character.h
 *
 *  Created on: Sep 3, 2020
 *      Author: sdady
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "Timer.h"
#include "math.h"

#include <GLES2/gl2.h>
#include "ShaderSprite.h"

namespace bsk {

class Character {
public:
   Character();
   virtual ~Character();

   void initialize();

   void update(Milliseconds dt);

   void resize(uint width, uint height);

   void setPosition(float x, float y);

   void move(float x, float y);

private:
   void updateTransform();

private:
   float const DEPTH = 1.0;
   const float CHARACTER_SIZE = 128;

   ShaderSprite      shader_;
   Image             img_;
   Material          mat_;
   Geometry          geometry_;
   Matrix4           transform_;

   float             screenWidth_;
   float             screenHeight_;
   Matrix4           projection_;

   std::vector<float>      verts_;
   std::vector<GLushort>   indices_;

   Vector3            position_;



};

} /* namespace bsk */

#endif /* SRC_CHARACTER_H_ */
