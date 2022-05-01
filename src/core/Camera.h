/*
 * Camera.h
 *
 *  Created on: Jul 5, 2021
 *      Author: shawn
 */

#ifndef SRC_GRAPHICS_CAMERA_H_
#define SRC_GRAPHICS_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace bsk {

class Camera {
public:
	Camera();
	virtual ~Camera();

	void initializeView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& upAxis);
	void initializeProj(float fov, float aspectRatio, float near, float far);

	void update();

	const glm::mat4x4& getView() const;

	const glm::mat4x4& getProjection() const;

private:
	glm::mat4x4   view_;
	glm::mat4x4   projection_;
};

} /* namespace bsk */

#endif /* SRC_GRAPHICS_CAMERA_H_ */
