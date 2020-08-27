/*
 * FontManager.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "FontManager.h"
#include "ImageLoader.h"

namespace bsk {

FontManager::FontManager() {
   ImageLoader::loadImage("assets/img/font.png", fontImg_);
}

FontManager::~FontManager() {

}

void FontManager::update() {
   for(auto font: fonts_) {
      font.render();
   }
}

void FontManager::addFont(const std::string& text, uint width, uint height) {
   Font font;
   font.initialize(text, width, height);
   fonts_.push_back(font);
}

} /* namespace bsk */
