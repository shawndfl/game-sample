/*
 * FontData.h
 *
 *  Created on: Aug 3, 2021
 *      Author: shawn
 */

#ifndef GRAPHICS_FONTDATA_H_
#define GRAPHICS_FONTDATA_H_

namespace bsk {

struct FontData {
      char         character;   /// The char
      int          sizeX;       /// Size of glyph
      int          sizeY;       /// Size of glyph
      int          bearingX;    /// Offset from baseline to left/top of glyph
      int          bearingY;    /// Offset from baseline to left/top of glyph
      unsigned int advance;     /// Offset to advance to next glyph
      float        u1;          /// upper left uv coordinates
      float        v1;          /// upper left uv coordinates
      float        u2;          /// bottom right uv coordinates
      float        v2;          ///  bottom right uv coordinates
  };

} /* namespace bsk */

#endif /* GRAPHICS_FONTDATA_H_ */
