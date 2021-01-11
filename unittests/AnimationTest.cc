#include "UnitTest++/UnitTest++.h"
#include "core/Logging.h"
#include "core/AnimationClip.h"

SUITE(Animation) {

/*************************************************/
TEST(LowerBoundTest) {
   bsk::AnimationClip clip;
   uint index = 0;

   std::vector< bsk::AnimationClip::Key> values;
   index = bsk::AnimationClip::find(values, 1);
   CHECK_EQUAL((uint)-1, index);

   values.push_back(bsk::AnimationClip::Key(2, 0));

   index = bsk::AnimationClip::find(values, 1);
   CHECK_EQUAL(0, index);

   index = bsk::AnimationClip::find(values, 2);
   CHECK_EQUAL(0, index);

   index = bsk::AnimationClip::find(values, 3);
   CHECK_EQUAL(0, index);
}

/*************************************************/
TEST(SearchTest) {
   bsk::AnimationClip clip;
   uint index = 0;

   std::vector<bsk::AnimationClip::Key> values;
   values.push_back(bsk::AnimationClip::Key(2,0));
   values.push_back(bsk::AnimationClip::Key(3,0));
   values.push_back(bsk::AnimationClip::Key(5,0));
   values.push_back(bsk::AnimationClip::Key(10,0));

   index = bsk::AnimationClip::find(values, 1);
   CHECK_EQUAL(0, index);

   index = bsk::AnimationClip::find(values, 2);
   CHECK_EQUAL(0, index);

   index = bsk::AnimationClip::find(values, 6);
   CHECK_EQUAL(2, index);

   index = bsk::AnimationClip::find(values, 11);
   CHECK_EQUAL(3, index);

}

/*************************************************/
TEST(SortTest) {
   bsk::AnimationClip clip;

   clip.addKey(2,1);
   clip.addKey(7,3);
   clip.addKey(20,4);
   clip.addKey(4,5);
   clip.addKey(9,6);
   clip.addKey(40,8);

   CHECK_EQUAL(2, clip.getKeys()[0].ms);
   CHECK_EQUAL(4, clip.getKeys()[1].ms);
   CHECK_EQUAL(7, clip.getKeys()[2].ms);
   CHECK_EQUAL(9, clip.getKeys()[3].ms);
   CHECK_EQUAL(20, clip.getKeys()[4].ms);
   CHECK_EQUAL(40, clip.getKeys()[5].ms);
}

/*************************************************/
TEST(DiscreteTest) {
   bsk::AnimationClip clip;

   clip.addKey(2,1);
   clip.addKey(4,5);
   clip.addKey(7,3);
   clip.addKey(9,6);
   clip.addKey(20,4);
   clip.addKey(40,8);

   CHECK_EQUAL(5, clip.evaluate(5,true));
   CHECK_EQUAL(8, clip.evaluate(50,true));

   CHECK_EQUAL(6, clip.evaluate(30));
   CHECK_EQUAL(8, clip.evaluate(60));
}

}
