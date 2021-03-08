/*
 * Character.h
 *
 *  Created on: Sep 3, 2020
 *      Author: sdady
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "math/Timer.h"
#include "math/math.h"
#include "core/AnimationClip.h"

#include "graphics/ShaderSprite.h"

namespace bsk {

class Character {
public:
   enum State {
        StIdle            = 0x00,     // 0
        StMovingRight     = 0x01,     // 1     1        1b
        StMovingLeft      = 0x02,     // 2     1<<1     10b
        StJumping         = 0x04,     // 4     1<<2     100b
        StFalling         = 0x08,     // 8     1<<3     1000b
        StHit             = 0x10,     // 16    1<<4     10000b
        StShoot           = 0x20,     // 32    1<<5     100000b

     };

   Character();

   virtual ~Character();

   void initialize();

   void update(Milliseconds dt);

   void resize(uint width, uint height);

   void setPosition(float x, float y);

   void move(float x, float y);

   void moveJump();

   /**
    * Handles a keyevent.
    * return true if handled else false
    */
   bool onKey(int key, int scancode, int action, int mods);

private:
   void updateTransform();

private:
   float const DEPTH             = 1.0;
   const float CHARACTER_SIZE    = 128;
   const float CHARACTER_SPEED   = 0.50;


   ShaderSprite      shader_;
   Image             img_;
   Material          mat_;
   Geometry          geometry_;
   Matrix4           transform_;

   float             screenWidth_;
   float             screenHeight_;
   Matrix4           projection_;

   std::vector<float>      verts_;
   std::vector<GLushort>   indices_;

   Vector3            position_;         /// Current position on the screen
   Vector3            velocity_;         /// the total velocity of the character
   Vector3            inputVelocity_;    /// the velocity based on the input of the user.

   // used for animations
   State              state_;            /// The state of the character

   AnimationClip      clip_;



};

} /* namespace bsk */

#endif /* SRC_CHARACTER_H_ */
