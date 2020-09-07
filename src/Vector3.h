/*
 * Vector3.h
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#ifndef SRC_VECTOR3_H_
#define SRC_VECTOR3_H_

namespace bsk {

/**
 * Vector3 class
 */
class Vector3 {
public:
   Vector3();
   Vector3(float x, float y, float z);
   virtual ~Vector3();

   void setUniform(int name);


   float x;
   float y;
   float z;
};

} /* namespace bsk */

#endif /* SRC_VECTOR3_H_ */
