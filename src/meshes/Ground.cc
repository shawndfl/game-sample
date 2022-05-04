/*
 * Ground.cc
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#include "Ground.h"
#include "graphics/Primitive.h"
#include "core/Camera.h"
#include "graphics/ImageLoader.h"
#include "core/Logging.h"

namespace bsk {

/*************************************************/
Ground::Ground() {
   initialized_ = false;

}

/*************************************************/
Ground::~Ground() {

}

/*************************************************/
void Ground::initialize() {

   if(!shader_.loadShaderFromFile("assets/shaders/phong.vert", "assets/shaders/phong.frag")) {
      initialized_ = false;
      return;
   }

   rotateX(-90);
   position_.y = -1;

   shader_.use();
   shader_.setMatrix4("model", world_);

   // hard code a point light
   shader_.setVec3("lightPos", glm::vec3(0, 10,0));
   shader_.setVec3("lightColor", glm::vec3(1.0,1.0,1.0));   // set the color to white
   shader_.setFloat("ambientStrength", 0.1);                 // set ambient scale

   //geometry_ = bsk::Primitive::createQuad();
   geometry_ = bsk::Primitive::createPlane(500, 500, 100, 100, 100);

   // texture
   bsk::Image img;
   if (bsk::ImageLoader::loadImage("assets/img/tileable_grass_00.png", img)) {
      texture_.setImage(img);
      LOGGL();
      initialized_ = true;
   }
}

/*************************************************/
void Ground::render(const Camera& camera) {

   if(!initialized_) {
      return;
   }

   shader_.use();

   //model = glm::rotate(model, glm::radians(clip_.evaluate()) , glm::vec3(1.0f, 0.0f, 0.0f));
   shader_.setMatrix4("model", world_);
   glm::mat4 normalMat = glm::transpose(glm::inverse(world_));
   shader_.setMatrix4("normalMat", normalMat);
   shader_.setMatrix4("view", camera.getView());
   shader_.setMatrix4("proj", camera.getProjection());

   texture_.apply();
   geometry_.makeActive();

   //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   glDrawElements(GL_TRIANGLES, geometry_.getPrimitiveCount(), GL_UNSIGNED_INT, 0);
}

} /* namespace bsk */
