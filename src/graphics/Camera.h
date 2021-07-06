/*
 * Camera.h
 *
 *  Created on: Jul 5, 2021
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_CAMERA_H_
#define SRC_GRAPHICS_CAMERA_H_

#include "math/Vector3.h"
#include "math/Matrix4.h"

namespace bsk {

class Camera {
public:
	Camera();
	virtual ~Camera();

	void initialize(const Vector3& eye, const Vector3& lookat, const Vector3& up);

private:
	Matrix4   view_;
	Matrix4   projection_;
};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_CAMERA_H_ */
