/*
 * Display.cc
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#include "Display.h"

#include "Logging.h"
#include "graphics/Render.h"

//#define GLFW_INCLUDE_ES2
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace bsk {

Display* Display::instance_ = nullptr;

/*************************************************/
void Display::create(GameEngine& game) {
   if(instance_ == nullptr) {
      instance_ = new Display(game);
   }
}

/*************************************************/
Display* Display::get() {
   if(instance_ == nullptr){
      LOGD("Call Display::create() first");
   }
   return instance_;
}


/*************************************************/
Display::Display(GameEngine& game) :
      game_(game) {

}

/*************************************************/
Display::~Display() {

}

/*************************************************/
void errorCallback(int error, const char* description) {
    LOGE("Glfw Error (" << error << "): " <<  description);
}

/*************************************************/
void Display::resizeEvent(uint width, uint height) {
   game_.resize(width, height);
}

/*************************************************/
void resize(GLFWwindow* window, int width, int height) {
   Display::get()->resizeEvent((uint)width, (uint)height);
}

/*************************************************/
void Display::keyboardEvent(int key, int scancode, int action, int mods) {
   game_.keyEvent(key, scancode, action, mods);
}

/*************************************************/
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
   Display::get()->keyboardEvent(key, scancode, action, mods);
}

/*************************************************/
void Display::runDisplay(uint width, uint height) {

   GLFWwindow* window;

   glfwSetErrorCallback(errorCallback);

   if(!glfwInit()) {
	   LOGE("Error glfwInit()");
   }
   //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
   //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

   window = glfwCreateWindow(width, height, "Block Simulated Kingdom", NULL, NULL);
   glfwMakeContextCurrent(window);

   gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

   if(!game_.start(width, height)) {
      LOGD("Error with start.");
      exit(1);
   }

   glfwSetKeyCallback(window, &keyboard);
   glfwSetWindowSizeCallback(window, &resize);

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      if(!game_.update()) {
         break;
      }

      glfwSwapBuffers(window);
   }

   game_.dispose();

   glfwTerminate();
}

}
