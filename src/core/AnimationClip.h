/*
 * AnimationClip.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#ifndef SRC_ANIMATIONCLIP_H_
#define SRC_ANIMATIONCLIP_H_

#include "math/Timer.h"
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

   float evaluate(bool discrete = false ) const;

   float evaluate(Milliseconds ms, bool discrete = false ) const;

   /**
    * Update the animation time
    */
   void update(Milliseconds dt);

   Milliseconds getMax() const;

   void play();

   void pause();

   void setLoop(bool loop);

   /**
    * Used to find something in a list
    */
   static uint find(const std::vector<Key>& list, float value);

   bool operator() (const Key& a, const Key& b) const;

   const std::vector<Key>& getKeys() const;

private:
   std::vector<Key>        keys_;
   Milliseconds            milliseconds_;
   bool                    looping_;
   bool                    playing_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
