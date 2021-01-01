/*
 * Level1.h
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#ifndef SRC_LEVEL1_H_
#define SRC_LEVEL1_H_

#include "Timer.h"
#include "GameEngine.h"
#include "Character.h"
#include "Sprite.h"
#include "math.h"

namespace bsk {

class Level1 {
public:
   Level1();
   virtual ~Level1();

   bool start();

   void update(Milliseconds dt);

   void resize(uint width, uint height);

   void keyEvent(int key, int scancode, int action, int mods);

   void dispose();
private:

   Character  character_;
   Sprite     sprite_;

};

} /* namespace bsk */

#endif /* SRC_LEVEL1_H_ */
