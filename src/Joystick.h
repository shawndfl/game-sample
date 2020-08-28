/*
 * Joystick.h
 *
 *  Created on: Aug 27, 2020
 *      Author: sdady
 */

#ifndef SRC_JOYSTICK_H_
#define SRC_JOYSTICK_H_

#include <linux/joystick.h>
#include <string>

namespace bsk {

class Joystick {
public:

    Joystick();
    virtual ~Joystick();
    bool initialize(const std::string& device = "/dev/input/js0");

    void poll();
private:
    int fd_;
};

} /* namespace bsk */

#endif /* SRC_JOYSTICK_H_ */
