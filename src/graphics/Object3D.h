/*
 * Object3D.h
 *
 *  Created on: Jul 5, 2021
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_OBJECT3D_H_
#define SRC_GRAPHICS_OBJECT3D_H_

#include <memory>
#include "math/Vector3.h"
#include "math/Matrix4.h"

namespace bsk {

class Object3D {
public:
	Object3D();
	virtual ~Object3D();

	Matrix4   local_;
	Vector3   position_;
	Vector3   scale_;

	std::shared_ptr<Object3D> parent_;

};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_OBJECT3D_H_ */
