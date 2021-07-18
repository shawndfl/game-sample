/*
 * LevelSquare.h
 *
 *  Created on: Jul 6, 2021
 *      Author: shawn
 */

#ifndef SRC_LEVELS_LEVELSQUARE_H_
#define SRC_LEVELS_LEVELSQUARE_H_

#include "core/IScene.h"
#include "graphics/Camera.h"
#include "graphics/Cube.h"

class LevelSquare : public bsk::IScene {
public:
    LevelSquare();
    virtual ~LevelSquare();

    virtual bool start();

    virtual void update(bsk::Milliseconds dt);

    virtual void resize(uint width, uint height);

    virtual void keyEvent(int key, int scancode, int action, int mods);

    virtual void dispose();
private:

    unsigned int shaderProgram;
    unsigned int VAO;
    unsigned int texture;
};

#endif /* SRC_LEVELS_LEVELSQUARE_H_ */
