/*
 * GameEngine.cc
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#include "GameEngine.h"
#include "Render.h"
#include "FontManager.h"
#include "Logging.h"
#include "Joystick.h"
#include "Level1.h"

#include <unistd.h>

namespace bsk {

/*************************************************/
GameEngine::GameEngine()  {
   render_        = std::make_unique<Render>();
   fontManager_   = std::make_unique<FontManager>();
   joy_           = std::make_unique<Joystick>();
   level1_        = std::make_unique<Level1>();
   width_ = 1024;
   height_ = 1024;
}

/*************************************************/
GameEngine::~GameEngine() {
}

/*************************************************/
uint GameEngine::getWidth() {
    return width_;
}

/*************************************************/
uint GameEngine::getHeight() {
    return height_;
}

/*************************************************/
GameEngine& GameEngine::get() {
    static GameEngine* instance = new GameEngine();
    return *instance;
}

/*************************************************/
bool GameEngine::start(uint width, uint height) {

   if(!joy_->initialize()) {
      return false;
   }
   if(!render_->initialize(width, height)){
      return false;
   }
   if(!fontManager_->initialize()) {
      return false;
   }
   if(!level1_->start()){
      return false;
   }

   return true;
}

/*************************************************/
bool bsk::GameEngine::update() {

   render_->render();
   fontManager_->update();
   joy_->poll();

   Milliseconds dt =  timer_.getDelta();
   timer_.reset();
   level1_->update(dt);

   return true;
}

/*************************************************/
void bsk::GameEngine::dispose() {
   LOGD("Close engine");
   render_->dispose();

}

/*************************************************/
void GameEngine::resize(uint width, uint height) {
   render_->resize(width, height);
   fontManager_->resize(width, height);
   level1_ ->resize(width, height);
}

/*************************************************/
FontManager& GameEngine::getFontManager() {
    return *fontManager_;
}

/*************************************************/
Joystick& GameEngine::getJoy() {
    return *joy_;
}

/*************************************************/
Render& GameEngine::getRender() {
    return *render_;
}

}
