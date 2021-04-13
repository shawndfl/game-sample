/*
 * ShaderBlinnPhong.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERBLINNPHONG_H_
#define SRC_SHADERBLINNPHONG_H_

#include <string>
#include <vector>
#include <GLES2/gl2.h>

#include "graphics/ShaderProgram.h"
#include "graphics/Geometry.h"
#include "graphics/Material.h"
#include "math/math.h"

namespace bsk {

/*
 * Shader program that will require a material and geometry
 */
class ShaderBlinnPhong : public ShaderProgram {
public:

   ShaderBlinnPhong();

   virtual ~ShaderBlinnPhong();

   bool loadProgram();

   void enableProgram();

   bool bindMaterial(const Material& material);

   void setScreenSize(uint width, uint height);

   void setMVP(const Matrix4& mvp);
   void setColor(const Vector4& color);
   void setOffset(const Vector2& offset);
   void setScale(const Vector2& scale);


   int getNormal() const;
   int getPosition() const;
   int getTexture() const;
   int getByteStride() const;

   int getColor() const;
   int getDiffused() const;
   int getOverlay() const;
   int getUoffset() const;
   int getUscale() const;

   VertexAttributes getAttribute() const;

private:
   int getUniformLocation(const std::string& name);

   int getAttributeLocation(const std::string& name);
private:

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
   int          position_;
   int          texture_;
   int          normal_;

   int          byteStride_;

};

} /* namespace bsk */

#endif /* SRC_SHADERBLINNPHONG_H_ */
