/*
 * GameEngine.cc
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#include "GameEngine.h"
#include "Render.h"
#include "Logging.h"

namespace bsk {
/*************************************************/
GameEngine::GameEngine()  {
   render_ = std::make_unique<Render>();
}

/*************************************************/
GameEngine::~GameEngine() {
}

/*************************************************/
bool GameEngine::initialize() {
   return true;
}

/*************************************************/
bool GameEngine::start(uint width, uint height) {
   bool error = false;
   error |= !render_->initialize(width, height);

   return error;
}

/*************************************************/
bool bsk::GameEngine::update() {

   render_->render();

   return true;
}

/*************************************************/
void bsk::GameEngine::dispose() {
   LOGD("Close engine");
   render_->dispose();

}
}
