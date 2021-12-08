/*
 * Material.h
 *
 *  Created on: Aug 3, 2020
 *      Author: sdady
 */

#ifndef SRC_MATERIAL_H_
#define SRC_MATERIAL_H_

#include "graphics/Texture.h"
#include "math/Math.h"

namespace bsk {

class Material {
public:
	Material();
	virtual ~Material();

	void apply() const;

	const Texture& getDiffused() const;
	void setDiffused(const Texture &diffused);
	float getOpacity() const;
	void setOpacity(float opacity);
	const Texture& getOverlay() const;
	void setOverlay(const Texture &overlay);
	bool isTransparent() const;
	void setTransparent(bool transparent);

private:
    Texture     diffused_;		/// the main texture
    Texture     overlay_;		/// The overlay texture

    float       opacity_;      /// Opacity

    bool        transparent_;	/// If this material is transparent

    glm::vec4   color_;
    float       uscale_;
    float       vscale_;
    float       uoffset_;
    float       voffset_;
};

} /* namespace bsk */

#endif /* SRC_MATERIAL_H_ */
