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

}

/*************************************************/
Ground::~Ground() {

}

/*************************************************/
void Ground::initialize() {
   shader_.loadShaderFromFile("assets/shaders/texture.vert", "assets/shaders/texture.frag");

   glm::mat4 model(1);

   model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

   shader_.use();
   shader_.setMatrix4("model", world_);

   //geometry_ = bsk::Primitive::createQuad();
   geometry_ = bsk::Primitive::createPlane(2, 2, 10, 2);

   // texture
   bsk::Image img;
   if (bsk::ImageLoader::loadImage("assets/img/Bricks.png", img)) {
      texture_.setImage(img);
      LOGGL();
   }
}

/*************************************************/
void Ground::render(const Camera& camera) {

   shader_.use();

   //model = glm::rotate(model, glm::radians(clip_.evaluate()) , glm::vec3(1.0f, 0.0f, 0.0f));
   shader_.setMatrix4("model", world_);
   shader_.setMatrix4("view", camera.getView());
   shader_.setMatrix4("proj", camera.getProjection());

   texture_.apply();
   geometry_.makeActive();

   //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   glDrawElements(GL_TRIANGLES, geometry_.getPrimitiveCount(), GL_UNSIGNED_INT, 0);
}

} /* namespace bsk */
