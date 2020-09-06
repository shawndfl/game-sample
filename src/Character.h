/*
 * Character.h
 *
 *  Created on: Sep 3, 2020
 *      Author: sdady
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "Timer.h"
#include "ShaderProgram.h"

#include <GLES2/gl2.h>

namespace bsk {

class Character {
public:
   Character();
   virtual ~Character();

   void initialize();

   void update(Milliseconds dt);

private:

   ShaderProgram     shader_;
   Image             img_;
   Material          mat_;
   Geometry          geometry_;
};

} /* namespace bsk */

#endif /* SRC_CHARACTER_H_ */
