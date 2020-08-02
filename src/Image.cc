/*
 * Image.cc
 *
 *  Created on: Aug 2, 2020
 *      Author: sdady
 */

#include "Image.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
Image::Image() {
   width_      = 512;
   height_     = 512;
   colorType_  = (Image::ColorType)( (int)Image::CTColor | (int)Image::CTAlpha);
   bitDepth_   = Image::BitDepth8;
   numberOfPasses_ = 0;
   data_       = nullptr;
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

   data_       =  new unsigned char*[height_];
   for (uint y = 0; y < height_; y++) {
      data_[y] = new unsigned char[rowBytes];
   }

}

/*************************************************/
unsigned char** Image::getImageData() const {
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
      LOGD("Pointer " << " " << height_);
      for (uint i = 0; i < height_; i++) {
         LOGD("i " << i);
         delete[] data_[i];
      }
      delete[] data_;
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

} /* namespace bsk */
