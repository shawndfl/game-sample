/*
 * FontManager.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "FontManager.h"

namespace bsk {

FontManager::FontManager() {
   // TODO Auto-generated constructor stub

}

FontManager::~FontManager() {
   // TODO Auto-generated destructor stub
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
