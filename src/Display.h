/*
 * Display.h
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <memory>
#include "GameEngine.h"

namespace bsk {
/**
 * The display this class uses glfw3 for ubuntu
 */
class Display {
public:
   virtual ~Display();

   void runDisplay(uint width, uint height);

   void resize(uint width, uint height);

   static void create(GameEngine& renderer);

   static Display* get();

private:
   /**
    * Singleton
    */
   Display(GameEngine& renderer);

private:

   static Display*   instance_;
   GameEngine&       game_;
};
}

#endif /* SRC_DISPLAY_H_ */
