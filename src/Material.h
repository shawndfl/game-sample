/*
 * Material.h
 *
 *  Created on: Aug 3, 2020
 *      Author: sdady
 */

#ifndef SRC_MATERIAL_H_
#define SRC_MATERIAL_H_

#include "Texture.h"

namespace bsk {

class Material {
public:
   Material();
   virtual ~Material();

private:
   Texture   diffused_;
   Texture   texture2_;

   float     opacity_;     /// Opacity

   bool      transparent_;
};

} /* namespace bsk */

#endif /* SRC_MATERIAL_H_ */
