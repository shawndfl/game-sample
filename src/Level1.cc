/*
 * Level1.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include "Level1.h"
#include "Joystick.h"

namespace bsk {

/*************************************************/
Level1::Level1() {

}

/*************************************************/
Level1::~Level1() {

}

/*************************************************/
void Level1::start() {

}

/*************************************************/
void Level1::update(Milliseconds dt) {

   Joystick& joystick = GameEngine::get().getJoy();
   if(joystick.getState().type == JS_EVENT_BUTTON) {
         if(joystick.getState().number == 9) {

         }
     }


}

} /* namespace bsk */
