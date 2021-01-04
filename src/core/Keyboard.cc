/*
 * Keyboard.cc
 *
 *  Created on: Sep 7, 2020
 *      Author: sdady
 */

#include "Keyboard.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Logging.h"

namespace bsk {

/*************************************************/
Keyboard::Keyboard() {
   fd_ = -1;
   memset(&event_, 0, sizeof(event_));
   memset(&state_, 0, sizeof(state_));
}

/*************************************************/
Keyboard::~Keyboard() {
}

/*************************************************/
bool Keyboard::initialize(const std::string& device) {
   fd_ = open(device.c_str(), O_RDONLY);
   if( fd_ == -1 ) {
      LOGD("Cannot open keyboard: " << device);
   }

   int flags = fcntl(fd_, F_GETFL, 0);
   fcntl(fd_, F_SETFL, flags | O_NONBLOCK);

   return true;
}

/*************************************************/
void Keyboard::poll() {

   if (fd_ != -1) {
      int bytes = read(fd_, &event_, sizeof(event_));
      if (bytes > 0) {
         if (event_.type & EV_KEY) {
            state_.keys[event_.code] = event_.value;
            LOGD("Hit key: " << (int)event_.code << " = " << (int) event_.value);
         }
      }
   }

}

} /* namespace bsk */
