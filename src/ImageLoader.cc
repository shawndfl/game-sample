/*
 * ImageLoader.cc
 *
 *  Created on: Aug 1, 2020
 *      Author: sdady
 */

#include "ImageLoader.h"
#include "Logging.h"

#define PNG_DEBUG 3
#include <libpng/png.h>

namespace bsk {


/*************************************************/
bool read_png_file(const char* filename, Image& image) {

   png_structp png_ptr;
   png_infop info_ptr;
   unsigned char header[8] = {0};    // 8 is the maximum size that can be checked

   /* open file and test for it being a png */
   FILE* fp = fopen(filename, "rb");
   if (!fp) {
      LOGD("Error reading: " << filename);
      return false;
   }

   size_t size = fread(header, 1, 8, fp);
   if (size == 0 || png_sig_cmp(header, 0, 8)) {
      LOGD(filename << " not recognized as a PNG file");
      return false;
   }

   /* initialize stuff */
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

   if (!png_ptr) {
      LOGD("Error creating read struct: " << filename);
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr) {
      LOGD("png_create_info_struct: " << filename);
   }

   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("Error during init_io: " << filename);
   }

   png_init_io(png_ptr, fp);
   png_set_sig_bytes(png_ptr, 8);

   png_read_info(png_ptr, info_ptr);

   image.Initialize(
         png_get_image_width(png_ptr, info_ptr),
         png_get_image_height(png_ptr, info_ptr),
         (Image::BitDepth) png_get_bit_depth(png_ptr, info_ptr),
         (Image::ColorType) png_get_color_type(png_ptr, info_ptr),
         png_get_rowbytes(png_ptr, info_ptr));

   png_read_update_info(png_ptr, info_ptr);

   /* read file */
   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("Error during read_image: " << filename);
      return false;
   }
   const int rowStep = png_get_rowbytes(png_ptr, info_ptr);

   for(uint i = 0; i < image.getHeight(); i++) {
      unsigned char* offset = image.getImageData() + (i * rowStep);
      png_read_row(png_ptr, offset, NULL);
   }

   fclose(fp);

   return true;
}

/*************************************************/
bool write_png_file(const char* filename, const Image& image) {

   png_structp png_ptr;
   png_infop info_ptr;

   /* create file */
   FILE* fp = fopen(filename, "wb");
   if (!fp) {
      LOGD("[write_png_file] File %s could not be opened for writing "<< filename);
      return false;
   }

   /* initialize stuff */
   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

   if (!png_ptr) {
      LOGD("[write_png_file] png_create_write_struct failed");
      return false;
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr) {
      LOGD("[write_png_file] png_create_info_struct failed");
      return false;
   }

   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("[write_png_file] Error during init_io");
      return false;
   }

   png_init_io(png_ptr, fp);

   /* write header */
   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("[write_png_file] Error during writing header");
      return false;
   }

   png_set_IHDR(png_ptr,
         info_ptr,
         image.getWidth(),
         image.getHeight(),
         image.getBitDepth(),
         image.getColorType(),
         PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE,
         PNG_FILTER_TYPE_BASE);

   png_write_info(png_ptr, info_ptr);

   /* write bytes */
   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("[write_png_file] Error during writing bytes");
      return false;
   }

   for (uint i = 0; i < image.getHeight(); i++) {
   //for (int i = (int)image.getHeight() - 1; i >= 0; i--) {
      unsigned char* offset = image.getImageData() + (i * image.getRowBytes());
      png_write_row(png_ptr, offset);
   }

   /* end write */
   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("[write_png_file] Error during end of write");
      return false;
   }

   png_write_end(png_ptr, NULL);

   fclose(fp);

   return true;
}

/*************************************************/
ImageLoader::ImageLoader() {

}

/*************************************************/
ImageLoader::~ImageLoader() {

}

/*************************************************/
bool ImageLoader::loadImage(const std::string& filename, Image& image) {

   bool result =  read_png_file(filename.c_str(), image);
   return result;
}

/*************************************************/
bool ImageLoader::saveImage(const std::string& filename, const Image& image) {

   bool result =  write_png_file(filename.c_str(), image);
   return result;
}

} /* namespace bsk */
