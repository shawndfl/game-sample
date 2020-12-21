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
}

/*************************************************/
Character::~Character() {

}

/*************************************************/
void Character::initialize() {
   LOGD("Initialize Character ");

   shader_.loadProgram();
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

   float characterSize = 32;
   Vector2 pos(50, 20);

   // pos
   verts_.push_back(pos.x - characterSize);
   verts_.push_back(pos.y - characterSize);
   verts_.push_back(5);

   //tex
   verts_.push_back(0);
   verts_.push_back(0);

   // pos
   verts_.push_back(pos.x + characterSize);
   verts_.push_back(pos.x - characterSize);
   verts_.push_back(5);

   //tex
   verts_.push_back(1);
   verts_.push_back(0);

   // pos
   verts_.push_back(pos.x + characterSize);
   verts_.push_back(pos.x + characterSize);
   verts_.push_back(5);

   //tex
   verts_.push_back(1);
   verts_.push_back(1);

   // pos
   verts_.push_back(pos.x - characterSize);
   verts_.push_back(pos.x + characterSize);
   verts_.push_back(5);

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

   Vector4 color(1,1,1,1);
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
void Character::resize(uint width, uint height) {
   screenWidth_ = width;
   screenHeight_ = height;
   shader_.setScreenSize(width, height);
}

/*************************************************/
void Character::setPosition(float x, float y) {
   transform_.setTranslation(x, y, 0);
   Matrix4 view;
   view.createLookAt(Vector3::ZERO, Vector3::FORWARD, Vector3::UP );

   Matrix4 projection;
   //projection.createProjection(45, screenWidth_ / screenHeight_, 1, 1000);
   projection.createOrthographic(-100, 100, -100, 100, .01, 1000);
   
   Matrix4 mvp = projection * view *  transform_;

   shader_.setMVP(mvp);
}

/*************************************************/
void Character::move(float x, float y) {
   Vector3 p = transform_.getTranslation();
   setPosition(p.x + x, p.y + y);
}

} /* namespace bsk */
