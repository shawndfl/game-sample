/*
 * AnimationClip.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#ifndef SRC_ANIMATIONCLIP_H_
#define SRC_ANIMATIONCLIP_H_

#include "math/Timer.h"
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

   AnimationClip();
   virtual ~AnimationClip();

   void addKey(uint ms, float value);

   float evaluate(uint ms, bool descreet ) const;

   uint getMax() const;

   void play();

   void pause();

   void setFlags(Flags animationFlags);

private:
   std::map<uint, float>   timeMap_;
   Timer                   timer_;
   Flags                   flags_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
