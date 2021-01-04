/*
 * AnimationClip.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#ifndef SRC_ANIMATIONCLIP_H_
#define SRC_ANIMATIONCLIP_H_

#include <map>

namespace bsk {

/**
 * Used to interpolate values
 */
class AnimationClip {
public:
   AnimationClip();
   virtual ~AnimationClip();

   void addKey(uint ms, float value);

   float evaluate(uint ms, bool descreet ) const;

   uint getMax() const;

private:
   std::map<uint, float>   timeMap_;
};

} /* namespace bsk */

#endif /* SRC_ANIMATIONCLIP_H_ */
