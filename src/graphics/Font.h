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
#include "math/Math.h"

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
   void initialize(const std::map<char, FontData>& charData,
           const std::string& text,
           int x,
           int y,
           int depth,
           float scale,
           const glm::vec4& color,
           int maxHeight,
           uint width,
           uint height);

   void render();

   void resize(const std::map<char, FontData>& charData, uint width, uint height);

   void dispose();

   const Geometry& getGeometry() const;

   /**
    * Gets the color of the font.
    * This is used by \ref FontManager
    */
   const glm::vec4& getColor() const;

private:
   void createBuffers(const std::map<char, FontData>& charData, uint width, uint height);

private:
   std::string   text_;
   int           posX_;
   int           posY_;
   int           depth_;
   float         scale_;
   int           maxHeight_;

   Geometry      geometry_;

   glm::vec4     color_;

};

} /* namespace bsk */

#endif /* SRC_FONT_H_ */
