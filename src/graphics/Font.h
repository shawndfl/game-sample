/*
 * Font.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <sys/types.h>
#include <string>
#include <map>
#include "math/math.h"

#include "graphics/ShaderFont.h"
#include "graphics/Geometry.h"
#include "graphics/ImageLoader.h"
#include "graphics/Material.h"

#include "graphics/FontData.h"

namespace bsk {

/**
 * This class will be used by FontManager to render text on the screen using a ShaderSprite
 */
class Font {
public:
   Font();
   virtual ~Font();

   /**
    * The text to display. Characters can be between ' ' and '~'.
    * '\n' will move text to the next line.
    *
    * screenX - the offset in screen space (-1, 1)
    * screenY - the offset in screen space (-1, 1)
    *
    */
   void initialize(std::map<char, FontData>& charData, const std::string& text, uint x, uint y, uint pixelSize = 16, const glm::vec4& color = glm::vec4(1,1,1,1));

   void render(const ShaderFont& shader);

   void dispose();

   const Geometry& getGeometry() const;

private:
   std::string   text_;
   int           screenX_;
   int           screenY_;

   Geometry      geometry_;

   glm::vec4     color_;

};

} /* namespace bsk */

#endif /* SRC_FONT_H_ */
