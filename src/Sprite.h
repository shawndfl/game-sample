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

   void updateScreenSize(uint width, uint height);

   void update(Milliseconds dt);

   void setTexture(const std::string texture);

};

} /* namespace bsk */

#endif /* SRC_SPRITE_H_ */
