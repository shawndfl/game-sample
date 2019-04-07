/*
 * Logging.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include <stdio.h>
#include <stdarg.h>

#include "Logging.h"

/*************************************************/
Logging::Logging() {
}

/*************************************************/
Logging::~Logging() {
}

/*************************************************/
Logging* Logging::get() {
   static Logging* instance = new Logging();
   return instance;
}

/*************************************************/
void Logging::logit(const char* logType, const char* file, int line,
      const char* text) {
   printf("%s %s(%d) %s\n", logType, file, line, text);
}

