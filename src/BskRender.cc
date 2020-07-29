/*
 * Render.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include "BskRender.h"

#include <GLES2/gl2.h>

/*************************************************/
Render::Render() :
      _initialized(false) {
}

/*************************************************/
Render::~Render() {
}

/*************************************************/
void Render::initialize() {
   _initialized = true;
}

/*************************************************/
void Render::render() {
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

/*************************************************/
bool Render::isInitialized() const {
   return _initialized;
}
