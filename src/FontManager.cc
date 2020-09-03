/*
 * FontManager.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "FontManager.h"
#include "ImageLoader.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
FontManager::FontManager() {
}

/*************************************************/
FontManager::~FontManager() {

}

/*************************************************/
void FontManager::update() {

   shader_.enableProgram();
   mat_.apply();

   for(auto pair: fonts_) {

      pair.second.render(shader_);
   }
}

/*************************************************/
bool FontManager::initialize() {
    shader_.loadProgram();
    Texture diffused;
    ImageLoader::loadImage("assets/img/font.png", fontImg_);
    diffused.setImage(fontImg_);
    mat_.setDiffused(diffused);

    diffused.apply(1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE0, 0);

    return true;
}

/*************************************************/
void FontManager::setFont(const std::string& id, const std::stringstream& text, float width, float height, float scale, Vector4 color) {
   fonts_[id].initialize(text.str(), width, height, scale, color);
}

} /* namespace bsk */
