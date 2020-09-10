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

   Vector3 operator-(const Vector3& rhs);
   Vector3& operator/(float scalar);
   Vector3& operator*(float scalar);

   Vector3& operator+(const Vector3& rhs);

   float length() const;

   Vector3& normalize();

   Vector3& cross(const Vector3& axis);

   Vector3& crossVectors(const Vector3& a, const Vector3& b);

   static const Vector3 ONE;
   static const Vector3 ZERO;
   static const Vector3 UP;
   static const Vector3 RIGHT;
   static const Vector3 FORWARD;

   float x;
   float y;
   float z;
};

} /* namespace bsk */

bsk::Vector3 operator-(const bsk::Vector3& lhs, const bsk::Vector3& rhs);

#endif /* SRC_VECTOR3_H_ */
