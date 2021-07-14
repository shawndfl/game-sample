/*
 * Render.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include "Render.h"
#include "core/Logging.h"
#include "glad/glad.h"

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
   resize(width, height);

   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

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
   LOGD("window size: " << width << "X" << height);

}

}
