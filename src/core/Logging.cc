/*
 * Logging.cc
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#include "Logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <iomanip>
#include <chrono>
#include "glad/glad.h"

namespace bsk {

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
void Logging::timestamp(char* outTimestamp, int len)
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    struct tm* time = localtime(&ltime);
    sprintf(outTimestamp, "%d:%d:%d", time->tm_hour, time->tm_min, time->tm_sec );
}

/*************************************************/
void Logging::openGlLog(const char* file, int line) {

    GLenum error;
    do {
        GLenum error = glGetError();
        std::stringstream errorString;
        switch (error) {
        case GL_NO_ERROR:
            break;
        case GL_INVALID_ENUM:
            errorString << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorString << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorString << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errorString << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            errorString << "GL_OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            errorString << "GL_STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            errorString << "GL_STACK_OVERFLOW";
            break;
        }

        if (error != 0) {
            logit('E', file, line, errorString);
        }
    } while (error != GL_NO_ERROR);
}

/*************************************************/
void Logging::logit(char type, const char* file, int line, const std::stringstream& text) {
   std::string filename = file;
   using namespace std::chrono;

   const int MAX_LEN = 15;
   int len = filename.size();
   if(filename.length() > MAX_LEN) {
      filename = "..." + filename.substr(len - MAX_LEN + 3);
   }

   auto now = std::chrono::system_clock::now();
   auto duration = now.time_since_epoch();
   long millis = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
   //long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
   millis = millis % 1000000;

   std::time_t tt = std::chrono::system_clock::to_time_t(now);
   tm* local_tm = localtime(&tt);

   std::cout << type << " "
        << std::setw(2) << std::setfill('0')  << local_tm->tm_hour
        << ":" << std::setw(2) << std::setfill('0')  << local_tm->tm_min
        << ":" << std::setw(2) << std::setfill('0')  << local_tm->tm_sec
        << "." << std::setw(6) << std::setfill('0') << millis << " "
        << std::setw(MAX_LEN) << std::setfill(' ') << filename
        << "(" << std::setw(3) << std::setfill('0')  << line << ") "
        << " " << text.str() << std::endl;
}

} //namespace bsk
