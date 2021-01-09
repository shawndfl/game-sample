/*
 * AnimationClip.cc
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#include "AnimationClip.h"
#include <cmath>

namespace bsk {

/*************************************************/
AnimationClip::AnimationClip() {
   flags_ = Ac_None;
}

/*************************************************/
AnimationClip::~AnimationClip() {
}

/*************************************************/
uint AnimationClip::find(const std::vector<uint>& list, float value) {

   uint min = 0;
   uint max = list.size()-1;
   uint mid = -1;
   while(min <= max) {
      mid = std::floor(max - min / 2);
      if(value < list[mid]) {
         max = mid - 1;
      } else if (value > list[mid]) {
         min = mid + 1;
      } else {
         return mid;
      }
   }
   return mid;
}

/*************************************************/
void AnimationClip::addKey(uint ms, float value) {
   uint index = find(times_, ms);
   if(index == (uint)-1) {

      //keys_.
   }
   //keys_ [index] = value;
}

/*************************************************/
float AnimationClip::evaluate(uint ms, bool descreet) const {
 return 0;
}

/*************************************************/
uint AnimationClip::getMax() const {
   if(times_.size() > 0) {
      return times_[times_.size()-1];
   } else {
      return 0;
   }
}

/*************************************************/
void AnimationClip::play() {
}

/*************************************************/
void AnimationClip::pause() {
}

/*************************************************/
void AnimationClip::setFlags(Flags animationFlags) {
}

} /* namespace bsk */
