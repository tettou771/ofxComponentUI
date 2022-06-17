#pragma once
#include "TextureView.h"

namespace ofxComponent {
    class ImageView : public TextureView {
    public:
        ImageView();

        // override from TextureView
        // if you override again, please call this
        // ???::onDraw() {
        // 	FboView::onDraw();
        //	// your code
        // }
        void onUpdate() override;
        void onDraw() override;
        void onDragEvent(ofDragInfo& info) override;

        ofTexture* getTexture() override;

        ofFloatColor getPixelColor(ofVec2f pos);
        ofFloatColor getPixelColorFromMouse();

        ofFloatImage img;

        // to set to global info
        string* fileInfo;

    protected:
        string imgPath;
        void load(string path);
        long long imgLastWriteTime;
        long long getFileTime(string path);

        // load image once per frame
        queue<ofFile> loadQueue;
        void loadFromQueueIfNotEmpty();
    };
}
