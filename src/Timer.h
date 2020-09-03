/*
 * Timer.h
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

namespace bsk {

typedef float Milliseconds;

class Timer {
public:
   Timer();
   virtual ~Timer();

   /**
    * resets the timer
    */
   void reset();

   /**
    * Gets the elapsed milliseconds
    */
   Milliseconds getDelta() const;

private:

   long seconds_;
   long nseconds_;

};

} /* namespace bsk */

#endif /* SRC_TIMER_H_ */
