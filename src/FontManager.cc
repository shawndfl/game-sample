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

      pair.second.render();
   }
}

/*************************************************/
bool FontManager::initialize() {
    shader_.loadProgram();
    Texture diffused;
    ImageLoader::loadImage("assets/img/font.png", fontImg_);
    diffused.setImage(fontImg_);
    mat_.setDiffused(diffused);

    return true;
}

/*************************************************/
void FontManager::setFont(const std::string& id, const std::stringstream& text, float width, float height, float scale) {
   fonts_[id].initialize(text.str(), width, height, scale);
   if (!shader_.bindGeometry(fonts_[id].getGeometry())) {

   }
}

} /* namespace bsk */
