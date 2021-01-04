/*
 * Render.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include "Render.h"
#include "core/Logging.h"

namespace bsk {

/*************************************************/
Render::Render() {
}

/*************************************************/
Render::~Render() {
}

/*************************************************/
bool Render::initialize(uint width, uint height) {

   LOGD("GL_VERSION: " << glGetString(GL_VERSION));
   LOGD("GL_RENDERER: " << glGetString(GL_RENDERER));

   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
   glViewport(0, 0, width, height);

   return true;
}

/*************************************************/
bool Render::render() {
   glClear(GL_COLOR_BUFFER_BIT);

   return true;

}

/*************************************************/
void Render::dispose() {
   LOGI("Close render");
   //glDeleteBuffers(1, &vbo);
}

/*************************************************/
void Render::resize(uint width, uint height) {
   glViewport(0, 0, width, height);

}

}
