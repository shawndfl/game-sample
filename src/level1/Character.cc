/*
 * Character.cc
 *
 *  Created on: Sep 3, 2020
 *      Author: sdady
 */

#include "../level1/Character.h"

#include "core/GameEngine.h"
#include "core/Joystick.h"
#include "core/Logging.h"
#include "graphics/ImageLoader.h"
#include "math/math.h"

namespace bsk {


/*************************************************/
bsk::Character::State operator|=(bsk::Character::State lhs, bsk::Character::State rhs) {
   bsk::Character::State newState = (bsk::Character::State)((int)lhs |(int) rhs);
   return newState;
}

/*************************************************/
Character::Character() {
   screenWidth_ = 800;
   screenHeight_ = 600;
   projection_.createOrthographic(-32, screenWidth_, 0, screenHeight_, 0, 10);
   position_ = Vector3(0,0,DEPTH);

   state_          = StIdle;
   animationFrame_ = 0;
}

/*************************************************/
Character::~Character() {

}

/*************************************************/
void Character::initialize() {
   LOGD("Initialize Character ");

   shader_.loadProgram();
   shader_.setScale(Vector2(1.0/32.0,1.0/32.0));

   Texture texture;
   ImageLoader::loadImage("assets/img/game.png", img_);
   texture.setImage(img_);
   mat_.setDiffused(texture);

   texture.apply(1);

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

   position_ += (inputVelocity_ + velocity_) * dt;

   updateTransform();

   if(state_ == StMovingLeft || state_ == StMovingRight) {
      if(animationTimer_.getDelta() > 200) {

         // use animation frame
         float offset = animationFrame_ * 32.0 / 1024.0;
         shader_.setOffset(Vector2(offset, 0));

         // loop
         animationFrame_++;
         if(animationFrame_ > 7) {
            animationFrame_ = 5;
         }

         // reset timeer
         animationTimer_.reset();
      }
   }


   // stop moving
   move(0, 0);

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
bool Character::onKey(int key, int scancode, int action, int mods) {

   // move right
   if (key == 262 && action > 0) {
      LOGD("Right");
      move(-1, 0);
   } else

   // move left
   if (key == 263 && action > 0) {
      move(1, 0);
   }

   return true;
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
   //LOGD("Moving " << x << ", " << y);
   inputVelocity_.x = x * CHARACTER_SPEED;
   inputVelocity_.y = y * CHARACTER_SPEED;
   if(x < 0) {
      state_ = StMovingLeft;
   } else if(x > 0) {
      state_ = StMovingRight;
   } else {
      state_ = StIdle;
   }

}

} /* namespace bsk */
