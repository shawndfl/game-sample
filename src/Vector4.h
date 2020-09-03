/*
 * Vector4.h
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#ifndef SRC_VECTOR4_H_
#define SRC_VECTOR4_H_

namespace bsk {

class Vector4 {
public:
   Vector4();
   Vector4(float x, float y, float z, float w);

   /**
    * Sets the uniform value
    */
   void setUniform(int name);

   virtual ~Vector4();

   static Vector4 ONE;
   static Vector4 ZERO;

   float x, y, z, w;
};

} /* namespace bsk */

#endif /* SRC_VECTOR4_H_ */
