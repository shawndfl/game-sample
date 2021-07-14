/*
 * Camera.cc
 *
 *  Created on: Jul 5, 2021
 *      Author: shawn
 */

#include "Camera.h"

namespace bsk {

/*************************************************/
Camera::Camera() {

}

/*************************************************/
Camera::~Camera() {
}

/*************************************************/
void Camera::initializeView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& upAxis) {
    view_ = glm::lookAt(eye, target, upAxis);
}

/*************************************************/
void Camera::initializeProj(float fov, float aspectRatio, float near, float far) {
    projection_ = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

/*************************************************/
void Camera::update() {

}

/*************************************************/
const glm::mat4x4& Camera::getView() const {
    return view_;
}

/*************************************************/
const glm::mat4x4& Camera::getProjection() const {
    return projection_;
}

} /* namespace bsk */
