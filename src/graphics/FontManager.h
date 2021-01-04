/*
 * FontManager.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_FONTMANAGER_H_
#define SRC_FONTMANAGER_H_

#include "graphics/Font.h"
#include <map>
#include <string>
#include <sstream>
#include <sys/types.h>
#include "math/Vector4.h"
#include "core/NoCopy.h"

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

   bool initialize(const std::string& imageFile = "assets/img/font.png");

   void update();

   void resize(uint width, uint height);

   void setFont(const std::string& id, const std::stringstream& text, uint x, uint y, uint pixelSize = 16, Vector4 color = Vector4(1,1,1,1));

private:
   std::map<std::string, Font>    fonts_;
   Texture                        fontTexture_;
   ShaderSprite                   shader_;

};

} /* namespace bsk */

#endif /* SRC_FONTMANAGER_H_ */
