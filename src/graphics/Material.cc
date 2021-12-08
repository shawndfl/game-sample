/*
 * Material.cc
 *
 *  Created on: Aug 3, 2020
 *      Author: sdady
 */

#include "Material.h"

namespace bsk {

/*************************************************/
Material::Material() {
    opacity_        = 1.0;
    transparent_    = false;

    color_          = glm::vec4(0,0,0,1);
    uscale_         = 1.0;
    vscale_         = 1.0;
    uoffset_        = 0.0;
    voffset_        = 0.0;
}

/*************************************************/
Material::~Material() {

}

/*************************************************/
const Texture& Material::getDiffused() const {
	return diffused_;
}

/*************************************************/
void Material::setDiffused(const Texture &diffused) {
	diffused_ = diffused;
}

/*************************************************/
float Material::getOpacity() const {
	return opacity_;
}

/*************************************************/
void Material::setOpacity(float opacity) {
	opacity_ = opacity;
}

/*************************************************/
const Texture& Material::getOverlay() const {
	return overlay_;
}

/*************************************************/
void Material::setOverlay(const Texture &overlay) {
	overlay_ = overlay;
}

/*************************************************/
bool Material::isTransparent() const {
	return transparent_;
}

/*************************************************/
void Material::setTransparent(bool transparent) {
	transparent_ = transparent;
}

/*************************************************/
void Material::apply() const {

	diffused_.apply(0);
}

} /* namespace bsk */
