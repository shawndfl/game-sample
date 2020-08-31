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

/**
 * Interface for the joystick device
 */
class Joystick {
public:

    Joystick();
    virtual ~Joystick();

    /**
     * Connects to a device
     */
    bool initialize(const std::string& device = "/dev/input/js0");

    /**
     * Updates the state
     */
    void poll();

    /**
     * Gets the current state of the joystick
     */
    const struct js_event& getState() const;
private:
    int              fd_;
    struct js_event  state_;
};

} /* namespace bsk */

#endif /* SRC_JOYSTICK_H_ */
