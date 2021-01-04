/*
 * Vector2.h
 *
 *  Created on: Aug 30, 2020
 *      Author: sdady
 */

#ifndef SRC_VECTOR2_H_
#define SRC_VECTOR2_H_

namespace bsk {

class Vector2 {
public:
   Vector2();
   Vector2(float x, float y);
   virtual ~Vector2();

   void setUniform(int name) const;


   float x;
   float y;
};

} /* namespace bsk */

#endif /* SRC_VECTOR2_H_ */
