#pragma once
#include "TextureView.h"

namespace ofxComponent {
	class FboView : public TextureView {
	public:
		FboView();

		// override from TextureView
		// if you override again, please call this
		// ???::onDraw() {
		// 	FboView::onDraw();
		//	// your code
		// }
		void onDraw() override;

		ofTexture* getTexture() override;

		void updatePixelMatrix();
		ofFloatColor getPixelColor(ofVec2f pos);

		ofFbo fbo;
		ofPixels pixels;
	};
}
