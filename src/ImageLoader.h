/*
 * ImageLoader.h
 *
 *  Created on: Aug 1, 2020
 *      Author: sdady
 */

#ifndef SRC_IMAGELOADER_H_
#define SRC_IMAGELOADER_H_

#include <string>

namespace bsk {

class ImageLoader {
public:
   ImageLoader();
   virtual ~ImageLoader();

   bool loadImage(const std::string& filename);

};

} /* namespace bsk */

#endif /* SRC_IMAGELOADER_H_ */
