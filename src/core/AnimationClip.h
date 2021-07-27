/*
 * AnimationClip.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#ifndef SRC_ANIMATIONCLIP_H_
#define SRC_ANIMATIONCLIP_H_

#include "math/Timer.h"
#include "math/mathCore.h"
#include <vector>
#include <map>

namespace bsk {

/**
 * Used to interpolate values
 */
class AnimationClip {
public:
   /**
    * the key for the animation frame
    */
   struct Key {
      Key(float ms, float value) : ms(ms), value(value) { }

      Key() : ms(0), value(0) { }

      Milliseconds   ms;
      float          value;
   };

   AnimationClip();

   virtual ~AnimationClip();

   void addKey(uint ms, float value);

   /**
    * this function only works if \ref update() is being called.
    */
   float evaluate(bool discrete = false ) const;

   /**
    * This evaluate function will ignore what update(dt)
    * has calculated for milliseconds_
    */
   float evaluate(Milliseconds ms, bool discrete = false ) const;

   /**
    * Update the animation time
    */
   void update(Milliseconds dt);

   /**
    * Gets the max time
    */
   Milliseconds getMax() const;

   /**
    * play the animation
    */
   void play(bool looping = false);

   /**
    * pause the animation
    */
   void pause();

   /**
    * Set if the animation should loop
    */
   void setLoop(bool loop);

   /**
    * Used to find something in a list
    */
   static uint find(const std::vector<Key>& list, float value);

   /**
    * Used for sorting keys
    */
   bool operator() (const Key& a, const Key& b) const;

   /**
    * Get the keys
    */
   const std::vector<Key>& getKeys() const;

   /**
    * is the animatoin looping
    */
   bool isLooping() const;

   /**
    * Get the current value of milliseconds from the update function
    */
   Milliseconds getMilliseconds() const;

   /**
    * is the animation playing. This will always be true if
    * looping is true
    */
   bool isPlaying() const;

private:
   std::vector<Key>        keys_;
   Milliseconds            milliseconds_;
   bool                    looping_;
   bool                    playing_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
