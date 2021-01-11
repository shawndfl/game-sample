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
   enum Flags {
      Ac_None       = 0x00,
      Ac_Running    = 0x01,
      Ac_PingPong   = 0x02,
      Ac_Loop       = 0x04,
      Ac_Descreet   = 0x08,
   };
   /**
    * the key for the animation frame
    */
   struct Key {
      Key(float ms, float value) : ms(ms), value(value) { }

      Key() : ms(0), value(0) { }

      float ms;
      float value;
   };

   AnimationClip();
   virtual ~AnimationClip();

   void addKey(uint ms, float value);

   float evaluate(uint ms, bool discrete = false ) const;

   uint getMax() const;

   void play();

   void pause();

   void setFlags(Flags animationFlags);

   /**
    * Used to find something in a list
    */
   static uint find(const std::vector<Key>& list, float value);

   bool operator() (const Key& a, const Key& b) const;

   Flags getFlags() const;

   const std::vector<Key>& getKeys() const;

private:
   std::vector<Key>        keys_;
   Timer                   timer_;
   Flags                   flags_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
