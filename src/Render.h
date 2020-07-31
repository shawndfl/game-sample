/*
 * Render.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_BSKRENDER_H_
#define SRC_BSKRENDER_H_

#include <GLES2/gl2.h>
#include <sys/types.h>

namespace bsk {
/**
 * This class is used to render the scene
 */
class Render {
public:
   Render();
   virtual ~Render();

   bool initialize(uint width, uint height);

   void  resize(uint width, uint height);

   bool render();

   void dispose();

private:
};
}
#endif /* SRC_BSKRENDER_H_ */
