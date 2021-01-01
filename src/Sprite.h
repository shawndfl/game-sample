/*
 * Sprite.h
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include "Timer.h"
#include "math.h"

#include <GLES2/gl2.h>
#include "ShaderSprite.h"

namespace bsk {

class Sprite {
public:
   Sprite();
   virtual ~Sprite();

   void initialize(const std::string& imageFile = "assets/img/game.png");

   void updateScreenSize(uint width, uint height);

   void update(Milliseconds dt);

   void setImageIndex(uint imageIndex);

   void setImagePosition( uint x, uint y);

private:

   static constexpr float QUAD_SIZE = 128;     /// A number that fits nice into our projection and view. This is scaled by the transform later
   static constexpr uint FRAME_SIZE   = 32;    /// The size of each frame in a window
   static constexpr uint IMAGE_WIDTH  = 1024;
   static constexpr uint IMAGE_HEIGHT = 1024;

   ShaderSprite      shader_;
   Material          mat_;
   Geometry          geometry_;
   Matrix4           transform_;

   float             screenWidth_;
   float             screenHeight_;
   Matrix4           projection_;
   float             imageDepth_;

   Vector3            position_;         /// Current position on the screen
};

} /* namespace bsk */

#endif /* SRC_SPRITE_H_ */
