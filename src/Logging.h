/*
 * Logging.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_LOGGING_H_
#define SRC_LOGGING_H_

/**
 * Logging class.
 */
class Logging {
public:
   virtual ~Logging();
   static Logging* get();

   void logit(const char* logType, const char* file, int line, const char* text);

private:
   Logging();

};

#define LOGD(LOG_TEXT) do { Logging::get()->logit("D", __FILE__, __LINE__, LOG_TEXT);  } while(0)


#endif /* SRC_LOGGING_H_ */
