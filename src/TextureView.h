#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {

    /// <summary>
    /// this is most basic view component
    /// simple draw the texture in rect
    /// </summary>
    class TextureView : public ofxComponentBase {
    public:
        TextureView();

        // override from ofxComponent
        // if you override again, please call this
        // ???::onDraw() {
        // 	TextureView::onDraw();
        //	// your code
        // }
        void onDraw() override;

        // please override this
        virtual ofTexture* getTexture() { return nullptr; };

        ofRectangle textureArea;
        bool stretchToWindow = false;

        void notifyTextureChanged();
        struct TextureChangedArgs{};
        ofEvent<TextureChangedArgs> textureChangedEvents;
        
        shared_ptr<Window> getParentWindow();
    };
}
