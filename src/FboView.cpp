#include "FboView.h"
using namespace ofxComponent;

FboView::FboView() {
}

void FboView::onDraw() {
	TextureView::onDraw();
}

ofTexture* FboView::getTexture() {
	if (fbo.isAllocated()) return &fbo.getTexture();
	else return nullptr;
}

void FboView::updatePixelMatrix() {
	fbo.readToPixels(pixels);
}

ofFloatColor FboView::getPixelColor(ofVec2f pos) {
	if (pos.x < 0 || pixels.getWidth() <= pos.x ||
		pos.y < 0 || pixels.getHeight() <= pos.y) {
		return ofFloatColor();
	}

	return pixels.getColor(pos.x, pos.y);
}
