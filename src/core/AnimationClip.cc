/*
 * AnimationClip.cc
 *
 *  Created on: Dec 29, 2020
 *      Author: sdady
 */

#include "AnimationClip.h"
#include <cmath>
#include "core/Logging.h"
#include <algorithm>

namespace bsk {

/*************************************************/
AnimationClip::AnimationClip() {
   flags_ = Ac_None;
}

/*************************************************/
AnimationClip::~AnimationClip() {
}

/*************************************************/
uint AnimationClip::find(const std::vector<Key>& list, float value) {

   // empty list
   if(list.size() == 0) {
      return (uint)-1;
   }

   // lower bound
   if(value < list[0].ms) {
      return 0;
   }

   // upper bound
   if (value > list[list.size()-1].ms) {
      return list.size()-1;
   }


   uint min = 0;
   uint max = (list.size()-1);
   uint mid = 0;

   // if there is only one element
   // and the value is less than this element
   // then return -1 else return index 0
   if( min == max) {
      return value < list[0].ms ? (uint)-1: 0;
   }

   while(min <= max) {

      if(max == min){
         mid = min;
      } else {
         mid = std::floor(max - min / 2);
      }

      if(value < list[mid].ms) {
         max = mid - 1;
      } else if (value > list[mid].ms) {
         min = mid + 1;
      } else {
         return mid;
      }
   }

   // closest value with out going over
   return mid;
}

/*************************************************/
bool AnimationClip::operator() (const Key& a, const Key& b) const {
   return a.ms < b.ms;
}

/*************************************************/
void AnimationClip::addKey(uint ms, float value) {
   Key key(ms, value);
   keys_.push_back(key);
   std::sort (keys_.begin(), keys_.end(), *this);
}

/*************************************************/
float AnimationClip::evaluate(uint ms, bool discrete) const {
   uint index = find(keys_, ms);

   // no items
   if(index == (uint)-1) {
      return 0;
   }

   if(discrete) {
      return keys_[index].value;
   } else {
      float t1 = keys_[index].ms;
      float v1 = keys_[index].value;
      float t2 = t1;
      float v2 = v1;
      if(index < keys_.size()-1) {
         t2 = keys_[index+1].ms;
         v2 = keys_[index+1].value;
      }

      float scale = 1.0;
      if(t2 - t1 != 0) {
         scale = (ms - t1) / (t2 - t1);
      }
      float value = v1 + scale * (v2 - v1);
      return value;
   }
   return 0;
}

/*************************************************/
uint AnimationClip::getMax() const {
   if(keys_.size() > 0) {
      return keys_[keys_.size()-1].ms;
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

/*************************************************/
AnimationClip::Flags AnimationClip::getFlags() const {
   return flags_;
}

/*************************************************/
const std::vector<AnimationClip::Key>& AnimationClip::getKeys() const {
   return keys_;
}

} /* namespace bsk */

