/*
 * LevelLight.h
 *
 *  Created on: Jul 14, 2021
 *      Author: shawn
 */

#ifndef SCENES_LEVELLIGHT_H_
#define SCENES_LEVELLIGHT_H_

#include "core/IScene.h"
#include "graphics/Geometry.h"
#include "graphics/Texture.h"

class LevelLight : public bsk::IScene {
public:
    LevelLight();
    virtual ~LevelLight();

    virtual bool start();

    virtual void update(bsk::Milliseconds dt);

    virtual void resize(uint width, uint height);

    virtual void keyEvent(int key, int scancode, int action, int mods);

    virtual void dispose();
private:
    bsk::Geometry    geometry_;
    unsigned int     shaderProgram_;
    bsk::Texture     texture_;

};

#endif /* SCENES_LEVELLIGHT_H_ */
