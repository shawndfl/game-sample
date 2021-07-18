/*
 * Level1.h
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#ifndef SRC_LEVEL1_H_
#define SRC_LEVEL1_H_


#include "game/Character.h"
#include "math/mathCore.h"
#include "math/Timer.h"
#include "core/GameEngine.h"
#include "graphics/Sprite.h"
#include "core/IScene.h"
#include "core/AnimationClip.h"
#include "graphics/Cube.h"

class Level1: public bsk::IScene {
public:
   Level1();
   virtual ~Level1();

   bool start();

   void update(bsk::Milliseconds dt);

   void resize(uint width, uint height);

   void keyEvent(int key, int scancode, int action, int mods);

   void dispose();
private:
   void loadMainTexture();
private:

   bsk::Texture    mainTexture_;
   bsk::Character  character_;
   bsk::Sprite     sprite_;

   bsk::Timer      timer_;
   uint       frameCount_;

   bsk::AnimationClip clip_;

   bsk::Cube        cube_;

   bsk::Camera      camera_;
};

#endif /* SRC_LEVEL1_H_ */
