/*
 * Texture.cc
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#include "Texture.h"
#include <GLES2/gl2.h>

namespace bsk {

/*************************************************/
Texture::Texture() {
   texture_ = 0;
}

/*************************************************/
Texture::~Texture() {
}

/*************************************************/
void Texture::setImage(const Image& img) {

   glGenTextures(1, &texture_);
   glBindTexture(GL_TEXTURE_2D, texture_);
   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // load the image
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getImageData());
   glGenerateMipmap(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, 0);
}

/*************************************************/
void Texture::dispose() {
   if(texture_ != 0) {

   }

}

} /* namespace bsk */
