/*
 * Coins.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#ifndef SRC_COINS_H_
#define SRC_COINS_H_

#include "Timer.h"
#include "math.h"

#include "ShaderSprite.h"

namespace bsk {

class Coins {
public:
   Coins();
   virtual ~Coins();

   void initialize();

   void update(Milliseconds dt);

   void resize(uint width, uint height);

   void setPosition(float x, float y);

private:
   void updateTransform();

private:
   float const DEPTH = 1.0;

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

   Vector3            position_;         /// Current position on the screen
   Vector3            velocity_;         /// the total velocity of the character
   Vector3            inputVelocity_;    /// the velocity based on the input of the user.

   // used for animations
   Timer              animationTimer_;   /// Used to cycle animation frames for the character
   int                animationFrame_;   /// Animation frame index. 0 is the left top most frame

};

} /* namespace bsk */

#endif /* SRC_COINS_H_ */
