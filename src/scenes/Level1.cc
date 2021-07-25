/*
 * Level1.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include <scenes/Level1.h>
#include <sstream>

#include "core/GameEngine.h"
#include "core/Joystick.h"
#include "graphics/FontManager.h"
#include "core/Logging.h"

/*************************************************/
Level1::Level1() {
   frameCount_ = 0;
}

/*************************************************/
Level1::~Level1() {

}

/*************************************************/
bool Level1::start() {

   // show some text
   std::stringstream stream;
   stream << "Hello!\nTest";
   bsk::GameEngine::get().getFontManager().setFont("title", stream, 0, 45, 32);

   // load the main texture that will
   // be shared between all sprites
   loadMainTexture();

   clip_.addKey(100, 0);
   clip_.addKey(200, 1);
   clip_.addKey(300, 2);
   clip_.addKey(400, 0);

   clip_.play(true);

   sprite_.initialize(mainTexture_);

   character_.initialize();

   character_.setPosition(20,0);

   cube_.initialize();

   //TODO initialize camera
   return true;
}

/*************************************************/
void Level1::update(bsk::Milliseconds dt) {

   clip_.update(dt);

   if(timer_.getDelta() > 1000) {
      double fps = frameCount_;
      std::stringstream stream;
      stream << "FPS: " << fps;

      // show frame rate
      bsk::GameEngine::get().getFontManager().setFont("fps", stream, 0, 0, 32);

      frameCount_ = 0;
      timer_.reset();
   }

   cube_.render(camera_);

   character_.update(dt);
   sprite_.update(dt);

   sprite_.setImageIndex(clip_.evaluate(true));

   frameCount_++;

}

/*************************************************/
void Level1::resize(uint width, uint height) {
   character_.resize(width, height);
}

/*************************************************/
void Level1::keyEvent(int key, int scancode, int action, int mods) {
   //LOGD("key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods);

   character_.onKey(key, scancode, action, mods);
}

/*************************************************/
void Level1::dispose() {
   mainTexture_.dispose();
}

/*************************************************/
void Level1::loadMainTexture() {
    bsk::Image img;
    bsk::ImageLoader::loadImage("assets/img/game.png", img);
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

