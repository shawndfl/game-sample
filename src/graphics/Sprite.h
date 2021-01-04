/*
 * Sprite.h
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include "math/Timer.h"
#include "math/math.h"

#include <GLES2/gl2.h>
#include "graphics/ShaderSprite.h"

namespace bsk {

/**
 * A sprite image that renders in screen space.
 *
 */
class Sprite {
public:
   Sprite();
   virtual ~Sprite();

   void initialize(const Texture& spriteTexture);

   void updateScreenSize(uint width, uint height);

   void update(Milliseconds dt);

   void setImageIndex(uint imageIndex);

   void setImagePosition( uint x, uint y);

   void dispose();

private:

   static constexpr float QUAD_SIZE = 128;     /// A number that fits nice into our projection and view. This is scaled by the transform later
   static constexpr uint FRAME_SIZE   = 32;    /// The size of each frame in a window
   static constexpr uint IMAGE_WIDTH  = 1024;
   static constexpr uint IMAGE_HEIGHT = 1024;

   ShaderSprite      shader_;
   Texture           spriteTexture_;
   Geometry          geometry_;
   Matrix4           transform_;

   float             screenWidth_;
   float             screenHeight_;
   float             imageDepth_;

   Vector3           position_;         /// Current position on the screen
};

} /* namespace bsk */

#endif /* SRC_SPRITE_H_ */
