/*
 * GameEngine.cc
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#include "GameEngine.h"
#include "graphics/Render.h"
#include "graphics/FontManager.h"
#include "core/Logging.h"
#include "core/Joystick.h"
#include "core/Keyboard.h"

#include <unistd.h>

namespace bsk {

/*************************************************/
GameEngine::GameEngine()  {
   render_        = std::make_unique<Render>();
   fontManager_   = std::make_unique<FontManager>();
   joy_           = std::make_unique<Joystick>();
   keyboard_      = std::make_unique<Keyboard>();

   width_ = 1024;
   height_ = 1024;
}

/*************************************************/
GameEngine::~GameEngine() {
}

/*************************************************/
void GameEngine::setScene(std::shared_ptr<bsk::IScene>& scene) {
   scene_ = std::shared_ptr<IScene>(scene);
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
void GameEngine::keyEvent(int key, int scancode, int action, int mods) {
   if(scene_) {
      scene_->keyEvent(key, scancode, action, mods);
   }
}

/*************************************************/
bool GameEngine::start(uint width, uint height) {

   joy_->initialize();
   keyboard_->initialize("/dev/input/event1");

   if(!render_->initialize(width, height)){
      return false;
   }
   if(!fontManager_->initialize()) {
      return false;
   }
   if(scene_ && !scene_->start()){
      return false;
   }

   return true;
}

/*************************************************/
bool bsk::GameEngine::update() {

   render_->render();
   fontManager_->update();
   joy_->poll();
   keyboard_ ->poll();

   Milliseconds dt =  timer_.getDelta();
   timer_.reset();

   if(scene_) {
      scene_->update(dt);
   }

   return true;
}

/*************************************************/
void bsk::GameEngine::dispose() {
   LOGD("Close engine");
   render_->dispose();

}

/*************************************************/
void GameEngine::resize(uint width, uint height) {
   width_ = width;
   height_ = height;
   render_->resize(width, height);
   fontManager_->resize(width, height);
   if(scene_) {
      scene_ ->resize(width, height);
   }
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
