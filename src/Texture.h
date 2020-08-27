/*
 * Texture.h
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#ifndef SRC_TEXTURE_H_
#define SRC_TEXTURE_H_

#include "Image.h"

namespace bsk {

class Texture {
public:
   Texture();
   virtual ~Texture();

   void setImage(const Image& img);

   void dispose();

   /**
    * Texture unit is between 0 and 32
    */
   void apply(uint textureUnit) const;

private:
   uint 	texture_;
};

} /* namespace bsk */

#endif /* SRC_TEXTURE_H_ */
