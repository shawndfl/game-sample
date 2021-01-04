/*
 * Level1.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include "Level1.h"

#include <sstream>

#include "core/GameEngine.h"
#include "core/Joystick.h"
#include "graphics/FontManager.h"
#include "core/Logging.h"

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

   loadMainTexture();

   sprite_.initialize(mainTexture_);

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
   mainTexture_.dispose();
}

/*************************************************/
void Level1::loadMainTexture() {
   Image img;
   ImageLoader::loadImage("assets/img/game.png", img);
   // once this is done the img can be disposed because the image is
   // now in video memory
   mainTexture_.setImage(img);
   mainTexture_.apply();

   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glBindTexture(GL_TEXTURE0, 0);
}

} /* namespace bsk */
