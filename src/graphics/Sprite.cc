/*
 * Sprite.cc
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#include "Sprite.h"
#include "ImageLoader.h"
#include "core/GameEngine.h"

namespace bsk {

/*************************************************/
Sprite::Sprite() {
   imageDepth_ = 1.0;
}

/*************************************************/
Sprite::~Sprite() {
}

/*************************************************/
void Sprite::dispose() {
   spriteTexture_.dispose();
   shader_.dispose();
}

/*************************************************/
void Sprite::initialize(const Texture& spriteTexture) {
   shader_.loadProgram();
   shader_.setScale(Vector2(1.0 /FRAME_SIZE, 1.0 / FRAME_SIZE));

   spriteTexture_ = spriteTexture;
   spriteTexture_.apply();

   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glBindTexture(GL_TEXTURE0, 0);

   const int vertCount = 4;         // 4 verts make a face
   const int vertAttributes = 5;    // Position(x,y,z) and texture (u,v)
   const int floatCount = vertCount * vertAttributes;
   const int indexCount = 6;        // 6 index for 2 triangles

   // create a quad for the character
   geometry_.initialize(floatCount, indexCount, Geometry::APos | Geometry::ATex1);
   std::vector<float>      verts;
   std::vector<GLushort>   indices;

   // pos
   verts.push_back(QUAD_SIZE);
   verts.push_back(0);
   verts.push_back(imageDepth_);

   //tex
   verts.push_back(0);
   verts.push_back(0);

   // pos
   verts.push_back(0);
   verts.push_back(0);
   verts.push_back(imageDepth_);

   //tex
   verts.push_back(1);
   verts.push_back(0);

   // pos
   verts.push_back(0);
   verts.push_back(QUAD_SIZE);
   verts.push_back(imageDepth_);

   //tex
   verts.push_back(1);
   verts.push_back(1);

   // pos
   verts.push_back(QUAD_SIZE);
   verts.push_back(QUAD_SIZE);
   verts.push_back(imageDepth_);

   //tex
   verts.push_back(0);
   verts.push_back(1);

   indices.push_back(0);
   indices.push_back(1);
   indices.push_back(2);

   indices.push_back(0);
   indices.push_back(2);
   indices.push_back(3);

   geometry_.setBuffers(verts, indices);

   setImagePosition(50, 500);
}

/*************************************************/
void Sprite::update(Milliseconds dt) {
   Vector4 color(1, 1, 1, 1);
   color.setUniform(shader_.getColor());

   Matrix4 projection;
   projection.createOrthographic(
         -QUAD_SIZE,
         GameEngine::get().getWidth(),
         0,
         GameEngine::get().getHeight(),
         0,
         10);
   transform_.setTranslation(position_);

   Matrix4 view;
   view.createLookAt(Vector3::ZERO, Vector3::FORWARD, Vector3::UP);

   Matrix4 mvp = projection * view * transform_;

   shader_.setMVP(mvp);

   shader_.enableProgram();
   spriteTexture_.apply();
   geometry_.makeActive(shader_);
   glDrawElements(GL_TRIANGLES, geometry_.IndexCount(), GL_UNSIGNED_SHORT,  NULL);
}

/*************************************************/
void Sprite::setImageIndex(uint imageIndex) {
}

/*************************************************/
void Sprite::setImagePosition(uint x, uint y) {
}

} /* namespace bsk */
