/*
 * Keyboard.h
 *
 *  Created on: Sep 7, 2020
 *      Author: sdady
 */

#ifndef SRC_KEYBOARD_H_
#define SRC_KEYBOARD_H_

#include <string>
#include <linux/input.h>

namespace bsk {

class Keyboard {
public:

   struct KeyboardState {
       signed short keys[KEY_CNT];
   };


   Keyboard();
   virtual ~Keyboard();

   /**
    * Connects to a device
    */
   bool initialize(const std::string& device = "/dev/input/event0");

   /**
    * Updates the state
    */
   void poll();

private:
   int               fd_;
   KeyboardState     state_;
   input_event       event_;
};

} /* namespace bsk */

#endif /* SRC_KEYBOARD_H_ */
