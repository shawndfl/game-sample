/*
 * Image.h
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_
#include "sys/types.h"
#include "NoCopy.h"

namespace bsk {

/**
 * Image loaded from libpng.
 * This can be loaded from ImageLoader.
 */
class Image : public NoCopy {
public:
   enum BitDepth {
      BitDepth1    = 1,
      BitDepth2    = 2,
      BitDepth4    = 4,
      BitDepth8    = 8,
      BitDepth16   = 16,
   };

   enum ColorType {
      CTPalette   = 1,
      CTColor     = 2,
      CTAlpha     = 4,
   };

   Image();

   virtual ~Image();

   void Initialize(int width, int height, BitDepth bitDepth, ColorType colorType, int rowBytes);

   unsigned char* getImageData() const;

   void setValue(int row, int col, float r, float g = 0, float b = 0, float a = 0);

   void dispose();
   BitDepth getBitDepth() const;
   ColorType getColorType() const;
   uint getHeight() const;
   uint getWidth() const;
   uint getRowBytes() const;

   uint getOpenGlColorType() const;

   uint getOpenGlByteDepth() const;

private:
   uint        width_;
   uint        height_;
   uint        rowBytes_;
   ColorType   colorType_;
   BitDepth    bitDepth_;
   int         numberOfPasses_;
   unsigned char* data_;

};

} /* namespace bsk */

#endif /* SRC_IMAGE_H_ */
