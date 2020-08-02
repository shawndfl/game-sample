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

int x, y;

bool read_png_file(const char* filename, png_bytepp image) {

   int width, height;
   png_byte color_type;
   png_byte bit_depth;

   png_structp png_ptr;
   png_infop info_ptr;
   int number_of_passes;
   unsigned char header[8];    // 8 is the maximum size that can be checked

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

   width = png_get_image_width(png_ptr, info_ptr);
   height = png_get_image_height(png_ptr, info_ptr);
   color_type = png_get_color_type(png_ptr, info_ptr);
   bit_depth = png_get_bit_depth(png_ptr, info_ptr);

   number_of_passes = png_set_interlace_handling(png_ptr);
   png_read_update_info(png_ptr, info_ptr);

   /* read file */
   if (setjmp(png_jmpbuf(png_ptr))) {
      LOGD("Error during read_image: " << filename);
      return false;
   }

   //*image = new png_bytep[height * png_get_rowbytes(png_ptr, info_ptr)];

   //row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
   //for (y = 0; y < height; y++) {
   //   row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
   //}

   //png_read_image(png_ptr, image);

   fclose(fp);

   return true;
}


namespace bsk {

/*************************************************/
ImageLoader::ImageLoader() {

}

/*************************************************/
ImageLoader::~ImageLoader() {

}

/*************************************************/
bool ImageLoader::loadImage(const std::string& filename) {

   return false;
}

} /* namespace bsk */
