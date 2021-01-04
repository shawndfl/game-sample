/*
 * Timer.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include "Timer.h"
#include <time.h>

namespace bsk {

/*************************************************/
Timer::Timer() {
   seconds_ = 0;
   nseconds_ = 0;
   reset();
}

/*************************************************/
Timer::~Timer() {
}

/*************************************************/
void Timer::reset() {
   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   seconds_ = now.tv_sec;
   nseconds_ = now.tv_nsec;
}

/*************************************************/
Milliseconds Timer::getDelta() const {
   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);

   if(now.tv_nsec < nseconds_) {
      now.tv_nsec += 1e9;
      now.tv_sec--;
   }
   long nseconds = now.tv_nsec - nseconds_;
   long seconds = now.tv_sec - seconds_;

   Milliseconds delta = seconds * 1e3 + nseconds * 1e-6;

   return delta;
}

} /* namespace bsk */
