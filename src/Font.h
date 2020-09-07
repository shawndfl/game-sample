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
#include <GLES2/gl2.h>
#include "Geometry.h"
#include "ShaderProgram.h"
#include "ImageLoader.h"
#include "Material.h"
#include "Vector4.h"

namespace bsk {

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
   void initialize(const std::string& text, uint x, uint y, uint pixelSize = 16, Vector4 color = Vector4(1,1,1,1));

   void render(const ShaderProgram& shader);

   void dispose();

   const Geometry& getGeometry() const;

private:
   std::string   text_;
   int           screenX_;
   int           screenY_;

   Geometry      geometry_;

   Vector4       color_;

};

} /* namespace bsk */

#endif /* SRC_FONT_H_ */
