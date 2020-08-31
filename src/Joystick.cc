/*
 * Joystick.cc
 *
 *  Created on: Aug 27, 2020
 *      Author: sdady
 */

#include "Joystick.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#include "Logging.h"

namespace bsk {

/*************************************************/
Joystick::Joystick() {
    fd_ = -1;
}

/*************************************************/
Joystick::~Joystick() {

}

/*************************************************/
bool Joystick::initialize(const std::string &device) {
    fd_ = open (device.c_str(), O_RDONLY);
    if(fd_ == -1) {
        LOGE("Can not open device " << device.c_str());
        return false;
    }

    int flags = fcntl(fd_, F_GETFL, 0);
    fcntl(fd_, F_SETFL, flags | O_NONBLOCK);

    char name[128] = {0};
    if (ioctl(fd_, JSIOCGNAME(sizeof(name)), name) < 0) {
        strncpy(name, "Unknown", sizeof(name));
    }
    LOGD("Name is: " << name);

    return true;

}

/*************************************************/
void Joystick::poll() {

    int res = read(fd_, &state_, sizeof(state_));
    if(res > 0) {
        switch(state_.type) {
        case JS_EVENT_BUTTON:
            LOGD("button event: " << (int)state_.number << " state " << state_.value);
            break;
        case JS_EVENT_AXIS:
            LOGD("axis event: " << (int)state_.number << " state " << state_.value);
            break;
        case JS_EVENT_INIT:
            LOGD("init");
            break;
        default:
            LOGD("Unknown event: " << (int)state_.type);
        }
    }
}

/*************************************************/
const struct js_event& Joystick::getState() const {
    return state_;
}

} /* namespace bsk */
