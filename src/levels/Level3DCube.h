/*
 * Level3DCube.h
 *
 *  Created on: Jul 6, 2021
 *      Author: shawn
 */

#ifndef SRC_LEVELS_LEVEL3DCUBE_H_
#define SRC_LEVELS_LEVEL3DCUBE_H_
#include "core/IScene.h"
#include "graphics/Camera.h"
#include "graphics/Cube.h"

class Level3DCube : public bsk::IScene {
public:
    Level3DCube();
    virtual ~Level3DCube();

    virtual bool start();

    virtual void update(bsk::Milliseconds dt);

    virtual void resize(uint width, uint height);

    virtual void keyEvent(int key, int scancode, int action, int mods);

    virtual void dispose();
private:
    bsk::Camera   camera_;
    bsk::Cube     cube_;
    bsk::ShaderBlinnPhong shader_;
};

#endif /* SRC_LEVELS_LEVEL3DCUBE_H_ */
