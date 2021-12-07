/*
 * FontManager.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_FONTMANAGER_H_
#define SRC_FONTMANAGER_H_

#include "graphics/Font.h"
#include "graphics/ShaderFont.h"
#include <map>
#include <string>
#include <sstream>
#include <sys/types.h>
#include "glm/glm.hpp"
#include "core/NoCopy.h"
#include "graphics/FontData.h"

namespace bsk {

/**
 * Manages displaying font on the screen. Initialize should be called once from the game engine.
 * If the level want to change the font texture call Initialize with a new imageFile path.
 *
 * Use setFont to draw and update text on the screen
 */
class FontManager: public NoCopy {
public:
   FontManager();
   virtual ~FontManager();

   bool initialize(const std::string& fontImage= "assets/fonts/font.png", const std::string& fontData = "assets/fonts/font.dat");

   void update();

   void resize(uint width, uint height);

   void setFont(const std::string& id, const std::string& text, uint x, uint y, uint pixelSize = 16, const glm::vec4& color = glm::vec4(1,1,1,1));


private:
   std::map<char, FontData>       fontData_;
   std::map<std::string, Font>    fonts_;
   Texture                        fontTexture_;
   ShaderFont                     shader_;

};

} /* namespace bsk */

#endif /* SRC_FONTMANAGER_H_ */
