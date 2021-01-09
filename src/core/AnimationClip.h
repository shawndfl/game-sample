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
   struct key {
      uint ms;
      float value;
   };

   AnimationClip();
   virtual ~AnimationClip();

   void addKey(uint ms, float value);

   float evaluate(uint ms, bool descreet ) const;

   uint getMax() const;

   void play();

   void pause();

   void setFlags(Flags animationFlags);

   /**
    * Used to find something in a list
    */
   static uint find(const std::vector<uint>& list, float value);

private:
   std::vector<uint>       times_;
   std::vector<double>     values_;
   Timer                   timer_;
   Flags                   flags_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
