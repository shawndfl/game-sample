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

namespace bsk {
/*************************************************/
GameEngine::GameEngine()  {
   render_        = std::make_unique<Render>();
   fontManager_   = std::make_unique<FontManager>();

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
   fontManager_->addFont("Hello", 0,0);

   return error;
}

/*************************************************/
bool bsk::GameEngine::update() {

   render_->render();
   fontManager_->update();
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
