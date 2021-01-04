/*
 * Logging.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_BSKLOGGING_H_
#define SRC_BSKLOGGING_H_

#include <iostream>
#include <string>
#include <sstream>

namespace bsk {
/**
 * Logging class.
 */
class Logging {
public:
   virtual ~Logging();
   static Logging* get();

   void logit(char type, const char* file, int line, const std::stringstream& text);
   void timestamp(char* outTimestamp, int len);
private:
   Logging();

};

} //namespace bsk


#define LOGD(STREAM) do {                 \
      std::stringstream MY_STREAM;        \
      MY_STREAM  << STREAM;              \
      bsk::Logging::get()->logit('D', __FILE__, __LINE__, MY_STREAM); \
} while(0)

#define LOGI(STREAM) do { \
      std::stringstream MY_STREAM;        \
      MY_STREAM  << STREAM;              \
      bsk::Logging::get()->logit('I', __FILE__, __LINE__, MY_STREAM); \
} while(0)

#define LOGW(STREAM) do { \
      std::stringstream MY_STREAM;        \
      MY_STREAM  << STREAM;              \
      bsk::Logging::get()->logit('W', __FILE__, __LINE__, MY_STREAM); \
} while(0)

#define LOGE(STREAM) do { \
      std::stringstream MY_STREAM;        \
      MY_STREAM  << STREAM;              \
      bsk::Logging::get()->logit('E', __FILE__, __LINE__, MY_STREAM); \
} while(0)

#endif /* SRC_BSKLOGGING_H_ */
