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

/**
 * Holds a reference to a single texture.
 * This class can load the image and apply the texture.
 * Remember to call dispose when done with this.
 */
class Texture {
public:
   Texture();
   virtual ~Texture();

   /**
    * Sets the image. \ref Image
    */
   void setImage(const Image& img);

   /**
    * Frees the opengl texture buffer
    */
   void dispose();

   /**
    * Texture unit is between 0 and 32
    */
   void apply(uint textureUnit = 0) const;

private:
   uint 	texture_;       /// The texture id
};

} /* namespace bsk */

#endif /* SRC_TEXTURE_H_ */
