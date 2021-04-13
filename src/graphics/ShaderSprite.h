/*
 * ShaderProgram.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERSPRITE_H_
#define SRC_SHADERSPRITE_H_

#include <string>
#include <vector>
#include <GLES2/gl2.h>

#include "ShaderProgram.h"
#include "Geometry.h"
#include "Material.h"
#include "math/math.h"

namespace bsk {

/*
 * Shader program that will require a material and geometry
 */
class ShaderSprite : public ShaderProgram {
public:

   ShaderSprite();

   virtual ~ShaderSprite();

   bool loadProgram();

   void enableProgram();

   bool setTexture(const Texture& texture);

   void setScreenSize(uint width, uint height);

   void setMVP(const Matrix4& mvp);
   void setColor(const Vector4& color);
   void setOffset(const Vector2& offset);
   void setScale(const Vector2& scale);

   virtual int getPosition() const;
   virtual int getTexture() const;
   virtual int getByteStride() const;

   VertexAttributes getAttribute() const;

   int getColor() const;
   int getDiffused() const;
   int getUoffset() const;
   int getUscale() const;

   void dispose();

private:
   int getUniformLocation(const std::string& name);

   int getAttributeLocation(const std::string& name);
private:

   Texture        texture_;
   GLuint         program_;

   // uniforms
   int          mvp_;
   int          diffused_;
   int          screen_;
   int          overlay_;
   int          ucolor_;
   int          uscale_;
   int          uoffset_;

   // attributes
   int          aPosition_;
   int          aTexture_;

   int          byteStride_;

};

} /* namespace bsk */

#endif /* SRC_SHADERSPRITE_H_ */
