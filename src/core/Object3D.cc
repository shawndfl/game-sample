/*
 * Object3D.cc
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#include "Object3D.h"

namespace bsk {

/*************************************************/
Object3d::Object3d() {
   autoUpdate_ = true;

   world_ = glm::mat4(1);
   local_ = glm::mat4(1);

   position_ = glm::vec3(0);
   scale_ = glm::vec3(1);
   rotation_= glm::quat(0,0,0,1);
   up_ = glm::vec3(0,1,0);

   worldNeedsUpdate_ = false;
   visible_ = true;
   parent_ = nullptr;
}

/*************************************************/
Object3d::~Object3d() {
}

/*************************************************/
void Object3d::updateMatrix() {
   local_ = bsk::compose(position_, rotation_, scale_);
   worldNeedsUpdate_ = true;
}

/*************************************************/
void Object3d::updateMatrixWorld(bool force) {

   if(autoUpdate_) {
      updateMatrix();
   }

   if(worldNeedsUpdate_ || force) {
      if(parent_ == nullptr) {
         world_ = local_;
      } else {
         world_ = parent_->world_ * local_;
      }
      force = true;
      worldNeedsUpdate_ = false;
   }

   for(auto child: children_) {
      child->updateMatrixWorld(force);
   }
}


/*************************************************/
Object3dPrt Object3d::add(Object3dPrt obj) {
   obj->parent_ = this;
   children_.push_back(obj);
   return obj;
}

/*************************************************/
void Object3d::applyMat4(const glm::mat4 &mat) {
}

/*************************************************/
void Object3d::applyQuaternion(const glm::quat &quat) {
}

/*************************************************/
void Object3d::attach(Object3dPrt obj) {
}

/*************************************************/
void Object3d::clone(bool recursive) {
}

/*************************************************/
void Object3d::copy(Object3dPrt obj, bool recursive) {
}

/*************************************************/
glm::vec3 Object3d::getWorldPosition() const {
   glm::vec3 world(0);
   return world;
}

/*************************************************/
glm::vec3 Object3d::getWorldDirection() const {
   glm::vec3 world(0);
   return world;
}

} /* namespace bsk */
