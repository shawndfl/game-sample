/*
 * ImageLoader.h
 *
 *  Created on: Aug 1, 2020
 *      Author: sdady
 */

#ifndef SRC_IMAGELOADER_H_
#define SRC_IMAGELOADER_H_

#include <string>
#include "Image.h"

namespace bsk {


class ImageLoader {
public:

   ImageLoader();
   virtual ~ImageLoader();

   static bool loadImage(const std::string& filename, Image& image);

   static bool saveImage(const std::string& filename, const Image& image);


};

} /* namespace bsk */

#endif /* SRC_IMAGELOADER_H_ */
