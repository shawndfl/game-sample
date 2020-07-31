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

/*************************************************/
Display::Display(GameEngine& game) :
      game_(game) {

}

/*************************************************/
Display::~Display() {

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

   game_.start(width, height);

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
