/*
 * Level1.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include "Level1.h"
#include <sstream>

#include "GameEngine.h"
#include "Joystick.h"
#include "FontManager.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
Level1::Level1() {

}

/*************************************************/
Level1::~Level1() {

}

/*************************************************/
bool Level1::start() {
   std::stringstream stream;
   stream << "Hello!\nTest";
   GameEngine::get().getFontManager().setFont("title", stream, 0, 0, 32);

   stream.str("");
   stream << "Hello2";
   GameEngine::get().getFontManager().setFont("title2", stream, 300, 300, 32);

   sprite_.initialize();

   character_.initialize();

   character_.setPosition(0,0);
   return true;
}

/*************************************************/
void Level1::update(Milliseconds dt) {

   character_.update(dt);
   sprite_.update(dt);

}

/*************************************************/
void Level1::resize(uint width, uint height) {
   character_.resize(width, height);
   sprite_.updateScreenSize(width, height);
}

/*************************************************/
void Level1::keyEvent(int key, int scancode, int action, int mods) {
   LOGD("key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods);

   character_.onKey(key, scancode, action, mods);
}

/*************************************************/
void Level1::dispose() {

}

} /* namespace bsk */
