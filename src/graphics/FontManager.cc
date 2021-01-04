/*
 * FontManager.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "graphics/FontManager.h"
#include "graphics/ImageLoader.h"
#include "core/Logging.h"

namespace bsk {

/*************************************************/
FontManager::FontManager() {
}

/*************************************************/
FontManager::~FontManager() {
   fontTexture_.dispose();
}

/*************************************************/
void FontManager::update() {

   shader_.enableProgram();
   fontTexture_.apply();

   Matrix4 projection;
   projection.createOrthographic(1, 600, 1, 500, 0, 10);

   Matrix4 mvp = projection;
   shader_.setMVP(mvp);

   for(auto pair: fonts_) {

      pair.second.render(shader_);
   }
}

/*************************************************/
bool FontManager::initialize(const std::string& imageFile) {
    shader_.loadProgram();
    Image img;
    ImageLoader::loadImage(imageFile, img);
    fontTexture_.setImage(img);

    fontTexture_.apply();
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE0, 0);

    return true;
}

/*************************************************/
void FontManager::resize(uint width, uint height) {
   shader_.setScreenSize(width, height);
}

/*************************************************/
void FontManager::setFont(const std::string& id, const std::stringstream& text, uint x, uint y, uint pixelSize, Vector4 color) {
   fonts_[id].initialize(text.str(), x, y, pixelSize, color);
}

} /* namespace bsk */
