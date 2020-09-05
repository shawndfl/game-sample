/*
 * Level1.h
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#ifndef SRC_LEVEL1_H_
#define SRC_LEVEL1_H_

#include "Timer.h"
#include "GameEngine.h"
#include "Character.h"

namespace bsk {

class Level1 {
public:
   Level1();
   virtual ~Level1();

   void start();

   void update(Milliseconds dt);
private:

   Character  character_;

};

} /* namespace bsk */

#endif /* SRC_LEVEL1_H_ */
