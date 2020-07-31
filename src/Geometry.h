/*
 * Geometry.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_GEOMETRY_H_
#define SRC_GEOMETRY_H_

#include "GLES2/gl2.h"

namespace bsk {

class Geometry {
public:
   Geometry();
   virtual ~Geometry();

   void initialize();

   void dispose();

   void makeActive();

protected:


};

} /* namespace bsk */

#endif /* SRC_GEOMETRY_H_ */
