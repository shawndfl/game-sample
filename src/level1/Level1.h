/*
 * Level1.h
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#ifndef SRC_LEVEL1_H_
#define SRC_LEVEL1_H_

#include "math/Timer.h"
#include "core/GameEngine.h"
#include "graphics/Sprite.h"
#include "math/math.h"
#include "core/IScene.h"
#include "Character.h"
#include "core/AnimationClip.h"

namespace bsk {

class Level1: public IScene {
public:
   Level1();
   virtual ~Level1();

   bool start();

   void update(Milliseconds dt);

   void resize(uint width, uint height);

   void keyEvent(int key, int scancode, int action, int mods);

   void dispose();
private:
   void loadMainTexture();
private:

   Texture    mainTexture_;
   Character  character_;
   Sprite     sprite_;

   Timer      timer_;
   uint       frameCount_;

   AnimationClip clip_;

};

} /* namespace bsk */

#endif /* SRC_LEVEL1_H_ */
