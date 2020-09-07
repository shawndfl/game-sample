/*
 * Display.cc
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#include "Display.h"

#include "Logging.h"
#include "Render.h"

#define GLFW_INCLUDE_ES2
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
void Display::resize(uint width, uint height) {
   game_.resize(width, height);
}

/*************************************************/
void rezise(GLFWwindow* window, int width, int height) {
   Display::get()->resize((uint)width, (uint)height);
}

/*************************************************/
void Display::runDisplay(uint width, uint height) {

   GLFWwindow* window;

   glfwInit();
   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

   window = glfwCreateWindow(width, height, "Block Simulated Kingdom", NULL, NULL);
   glfwMakeContextCurrent(window);

   if(!game_.start(width, height)) {
      LOGD("Error with start.");
      exit(1);
   }

   game_.resize(width, height);
   glfwSetWindowSizeCallback(window, &rezise);

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
