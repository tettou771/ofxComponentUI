#include "TextureView.h"
using namespace ofxComponent;

TextureView::TextureView() {
}

void TextureView::onDraw() {
	// draw texture in my rect
	auto texture = getTexture();
	if (texture && texture->isAllocated()) {
		if (stretchToWindow) {
			// scale to fit my rect
			textureArea = ofRectangle(0, 0, getWidth(), getHeight());
		}
		else {
			// scale to fit my rect
			// WITHOUT change aspect ratio
			textureArea = ofRectangle(0, 0, texture->getWidth(), texture->getHeight());
			textureArea.scaleTo(ofRectangle(0, 0, getWidth(), getHeight()));
		}
		texture->draw(textureArea);
	}
}

void TextureView::notifyTextureChanged() {
	auto args = TextureChangedArgs();
	ofNotifyEvent(textureChangedEvents, args);
}

shared_ptr<Window> TextureView::getParentWindow() {
    shared_ptr<Window> w = nullptr;
    auto child = static_pointer_cast<ofxComponentBase>(shared_from_this());
    while(true) {
        auto p = child->getParent();
        if (!p) return nullptr;
        
        auto w = dynamic_pointer_cast<Window>(p);
        if (w) {
            return w;
        } else {
            child = p;
        }
    }
    
    //return nullptr;
}
