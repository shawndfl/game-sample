/*
 * Character.cc
 *
 *  Created on: Sep 3, 2020
 *      Author: sdady
 */

#include "Character.h"
#include "GameEngine.h"
#include "Joystick.h"
#include "Logging.h"
#include "ImageLoader.h"
#include "math.h"

namespace bsk {

/*************************************************/
Character::Character() {
   screenWidth_ = 800;
   screenHeight_ = 600;
   projection_.createOrthographic(-32, screenWidth_, 0, screenHeight_, 0, 10);
   position_ = Vector3(0,0,DEPTH);
}

/*************************************************/
Character::~Character() {

}

/*************************************************/
void Character::initialize() {
   LOGD("Initialize Character ");

   shader_.loadProgram();
   shader_.setScale(Vector2(1.0/20.0,1.0));

   Texture diffused;
   ImageLoader::loadImage("assets/img/character.png", img_);
   diffused.setImage(img_);
   mat_.setDiffused(diffused);

   diffused.apply(1);

   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glBindTexture(GL_TEXTURE0, 0);

   // create a quad for the character
   geometry_.initialize(4*5, 6, Geometry::APos | Geometry::ATex1);
   // pos
   verts_.push_back(CHARACTER_SIZE);
   verts_.push_back(0);
   verts_.push_back(DEPTH);

   //tex
   verts_.push_back(0);
   verts_.push_back(0);

   // pos
   verts_.push_back(0);
   verts_.push_back(0);
   verts_.push_back(DEPTH);

   //tex
   verts_.push_back(1);
   verts_.push_back(0);

   // pos
   verts_.push_back(0);
   verts_.push_back(CHARACTER_SIZE);
   verts_.push_back(DEPTH);

   //tex
   verts_.push_back(1);
   verts_.push_back(1);

   // pos
   verts_.push_back(CHARACTER_SIZE);
   verts_.push_back(CHARACTER_SIZE);
   verts_.push_back(DEPTH);

   //tex
   verts_.push_back(0);
   verts_.push_back(1);

   indices_.push_back(0);
   indices_.push_back(1);
   indices_.push_back(2);

   indices_.push_back(0);
   indices_.push_back(2);
   indices_.push_back(3);

   geometry_.setBuffers(verts_, indices_);

   setPosition(0, 0);
}

/*************************************************/
void Character::update(Milliseconds dt) {

   Vector4 color(1,0,0,1);
   color.setUniform(shader_.getColor());

   Joystick& joystick = GameEngine::get().getJoy();
   if (joystick.getState().type == JS_EVENT_BUTTON) {
      LOGD("Hit button " << (int)joystick.getState().number);
      if (joystick.getState().number == 9) {
      }
   }
   if (joystick.getState().type == JS_EVENT_AXIS) {
      LOGD("Axis hit " << (int)joystick.getState().number << " = " << (int)joystick.getState().value);
   }

   shader_.enableProgram();
   mat_.apply();
   geometry_.makeActive(shader_);
   glDrawElements(GL_TRIANGLES, geometry_.IndexCount(), GL_UNSIGNED_SHORT, NULL);
}

/*************************************************/
void Character::updateTransform() {
   projection_.createOrthographic(-CHARACTER_SIZE, screenWidth_, 0, screenHeight_, 0, 10);
   transform_.setTranslation(position_);

   Matrix4 view;
   view.createLookAt(Vector3::ZERO, Vector3::FORWARD, Vector3::UP);

   Matrix4 mvp = projection_ * view * transform_;


   shader_.setMVP(mvp);
}

/*************************************************/
void Character::resize(uint width, uint height) {
   screenWidth_ = width;
   screenHeight_ = height;
   updateTransform();
   shader_.setScreenSize(width, height);
}

/*************************************************/
void Character::setPosition(float x, float y) {
   position_.x = x;
   position_.y = y;
   updateTransform();
}

/*************************************************/
void Character::move(float x, float y) {
   Vector3 p = transform_.getTranslation();
   setPosition(p.x + x, p.y + y);
}

} /* namespace bsk */
