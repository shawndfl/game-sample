/*
 * LevelCamera.h
 *
 *  Created on: Jul 26, 2021
 *      Author: shawn
 */

#ifndef SCENES_LEVELCAMERA_H_
#define SCENES_LEVELCAMERA_H_
#include "core/IScene.h"
#include "graphics/Geometry.h"
#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"
#include "core/AnimationClip.h"
#include "graphics/FontManager.h"
#include "graphics/ParticleEffect.h"
#include "math/Timer.h"

class LevelCamera : public bsk::IScene  {
public:
    LevelCamera();
    virtual ~LevelCamera();

    virtual bool start(uint width, uint height);

    virtual void update(bsk::Milliseconds dt);

    virtual void resize(uint width, uint height);

    virtual void keyEvent(int key, int scancode, int action, int mods);

    virtual void dispose();
private:
    bsk::Geometry       geometry_;
    bsk::Texture        texture_;
    bsk::ShaderProgram  shader_;

    bsk::AnimationClip  clip_;

    bsk::ParticleEffect  particle_;

    bsk::Timer           fps_;
    int                  frames_;
};

#endif /* SCENES_LEVELCAMERA_H_ */
