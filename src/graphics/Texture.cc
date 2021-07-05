/*
 * Texture.cc
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#include "Texture.h"
#include "core/Logging.h"
#include "glad/glad.h"

namespace bsk {

/*************************************************/
Texture::Texture() {
   texture_ = 0;
}

/*************************************************/
Texture::~Texture() {
   // not calling dispose here because texture gets passed around by value
   // and we might not want to dispose the texture each time.

   // Textures should be managed at a higher lever like a "Level" class
}

/*************************************************/
void Texture::setImage(const Image& img) {

   dispose();

   glGenTextures(1, &texture_);
   glBindTexture(GL_TEXTURE_2D, texture_);
   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // load the image
   glTexImage2D(GL_TEXTURE_2D, 0,
           img.getOpenGlColorType(),
           img.getWidth(),
           img.getHeight(),
           0, img.getOpenGlColorType(),
           img.getOpenGlByteDepth(),
           img.getImageData());
   glGenerateMipmap(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, 0);

   LOGD("Creating Texture");
}

/*************************************************/
void Texture::dispose() {
   if(texture_ != 0) {
      LOGD("Disposing: " << texture_);
	   glDeleteTextures(1, &texture_);
	   texture_ = 0;
   }
}

/*************************************************/
void Texture::apply(uint textureUnit) const {
	if(textureUnit > 32) {
		textureUnit = 0;
	}
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture_);

}

} /* namespace bsk */
