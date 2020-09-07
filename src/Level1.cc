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

   character_.initialize();
   return true;
}

/*************************************************/
void Level1::update(Milliseconds dt) {

   character_.update(dt);

}

/*************************************************/
void Level1::resize(uint width, uint height) {
   character_.resize(width, height);
}

} /* namespace bsk */
