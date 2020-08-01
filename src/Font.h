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

namespace bsk {

class Font {
public:
   Font();
   virtual ~Font();

   void initialize(const std::string& text, uint screenX, uint screenY);

   void render();

   void dispose();

private:
   std::string    text_;
   uint           screenX_;
   uint           screenY_;

   Geometry       geometry_;
   ShaderProgram  shader_;

   GLuint          fragment_;
   GLuint          vertex_;
   GLuint          program_;

   GLuint          vb_;
   GLuint          ib_;
};

} /* namespace bsk */

#endif /* SRC_FONT_H_ */
