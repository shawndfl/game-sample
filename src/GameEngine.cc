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

namespace bsk {

/*************************************************/
GameEngine::GameEngine()  {
   render_        = std::make_unique<Render>();
   fontManager_   = std::make_unique<FontManager>();
   joy_           = std::make_unique<Joystick>();

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
   bool error = false;

   error |= !joy_->initialize();
   error |= !render_->initialize(width, height);
   fontManager_->addFont("Hello!\nTest", -.8, 1);

   return error;
}

/*************************************************/
bool bsk::GameEngine::update() {

   render_->render();
   fontManager_->update();
   joy_->poll();
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

}

}
