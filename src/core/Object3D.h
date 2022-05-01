/*
 * Object3d.h
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#ifndef CORE_OBJECT3D_H_
#define CORE_OBJECT3D_H_

#include <vector>
#include <memory>
#include "math/Math.h"

namespace bsk {

class Object3d;

typedef std::shared_ptr< Object3d> Object3dPrt;

/**
 * Base node of a scene graph
 */
class Object3d {
public:
   Object3d();
   virtual ~Object3d();

   /**
    * Updates the transformation and all childern
    */
   void updateMatrix();

   /**
    * Updates the world matrix
    */
   void updateMatrixWorld(bool force = false);

   /**
    * Adds a new objects
    */
   Object3dPrt add(Object3dPrt obj);

   /**
    * Applies a transform to this object and calculates the postion, scale and rotation
    */
   void applyMat4(const glm::mat4& mat);

   /**
    * Applies a rotation.
    */
   void applyQuaternion(const glm::quat& quat);

   /**
    * Same as add but keeps the world transformation
    */
   void attach(Object3dPrt obj);

   /**
    * clones this object.
    */
   void clone(bool recursive = true);

   /**
    * Makes a copy of the given object and adds it as a child of
    * this object.
    */
   void copy(Object3dPrt obj, bool recursive = true);

   /**
    * Gets the world position
    */
   glm::vec3 getWorldPosition() const;

   /**
    * gets the pointing direction of this object in
    * world space.
    */
   glm::vec3 getWorldDirection() const;



public:
   Object3d* parent_;
   std::vector<Object3dPrt> children_;

   bool        autoUpdate_;     /// calculates the position, scale, and rotation each frame
   bool        worldNeedsUpdate_;

   glm::mat4   world_;
   glm::mat4   local_;

   glm::vec3   position_;
   glm::vec3   scale_;
   glm::quat   rotation_;
   glm::vec3   up_;

   bool        visible_;

};


} /* namespace bsk */

#endif /* CORE_OBJECT3D_H_ */
