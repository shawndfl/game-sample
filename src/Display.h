/*
 * Display.h
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <memory>
#include "Render.h"

namespace bsk {
/**
 * The display this class uses glfw3 for ubuntu
 */
class Display {
public:
   Display(Render& renderer);
   virtual ~Display();

   void runDisplay(uint width, uint height);

private:
   Render&   renderer_;
};
}

#endif /* SRC_DISPLAY_H_ */
