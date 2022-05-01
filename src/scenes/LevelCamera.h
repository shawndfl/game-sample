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
#include "meshes/Ground.h"
#include "graphics/FontManager.h"
#include "graphics/ParticleEffect.h"
#include "core/Camera.h"
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
    bsk::Camera         camera_;
    std::shared_ptr<bsk::Ground>    ground_;
    bsk::Object3d       root_;
    bsk::AnimationClip  clip_;

    bsk::ParticleEffect  particle_;

    bsk::Timer           fps_;
    int                  frames_;
};

#endif /* SCENES_LEVELCAMERA_H_ */
