/*
 * Image.cc
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#include "Image.h"
#include "Logging.h"
#include <GLES2/gl2.h>

namespace bsk {

/*************************************************/
Image::Image() {
   width_      = 512;
   height_     = 512;
   colorType_  = (Image::ColorType)( (int)Image::CTColor | (int)Image::CTAlpha);
   bitDepth_   = Image::BitDepth8;
   numberOfPasses_ = 0;
   data_       = nullptr;
   rowBytes_ = 0;
}

/*************************************************/
Image::~Image() {

}

/*************************************************/
void Image::Initialize(int width, int height, BitDepth bitDepth, ColorType colorType, int rowBytes) {
   width_      = width;
   height_     = height;
   colorType_  = colorType;
   bitDepth_   = bitDepth;
   numberOfPasses_ = 0;
   rowBytes_   = rowBytes;

   data_       =  new unsigned char[height_ * rowBytes_];

}

/*************************************************/
unsigned char* Image::getImageData() const {
   return data_;
}

/*************************************************/
void Image::setValue(int row, int col, float r, float g, float b, float a) {

   if(data_ != nullptr) {

   }
}

/*************************************************/
void Image::dispose() {
   if (data_ != nullptr) {
      delete data_;
      data_ = nullptr;
   }
}

/*************************************************/
Image::BitDepth Image::getBitDepth() const {
   return bitDepth_;
}

/*************************************************/
Image::ColorType Image::getColorType() const {
   return colorType_;
}

/*************************************************/
uint Image::getHeight() const {
   return height_;
}

/*************************************************/
uint Image::getWidth() const {
   return width_;
}

/*************************************************/
uint Image::getRowBytes() const {
   return rowBytes_;
}

/*************************************************/
uint Image::getOpenGlColorType() const {
    if((colorType_ & CTAlpha) > 0) {
        return GL_RGBA;
    } else {
        return GL_RGB;
    }
}

/*************************************************/
uint Image::getOpenGlByteDepth() const {
    switch (bitDepth_) {
    case BitDepth1:
        return GL_UNSIGNED_BYTE;
    case BitDepth2:
        return GL_UNSIGNED_BYTE;
    case BitDepth4:
        return GL_UNSIGNED_BYTE;
    case BitDepth8:
        return GL_UNSIGNED_BYTE;
    case BitDepth16:
        return GL_UNSIGNED_SHORT;
    default:
        return GL_UNSIGNED_BYTE;
    }
}

} /* namespace bsk */
