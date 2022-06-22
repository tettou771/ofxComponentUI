#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class ScrollBar : public ofxComponentBase {
    public:
        ScrollBar(){};
            
    private:
        //shared_ptr<ScrollView> parentScrollView;
    };

    class ScrollView : public View {
    public:

        enum ResizeMode {
            // resize to window
            Both,

            // resize width only
            Width,
            
            // resize height only
            Height,
            
            // doesn't resize
            // if bigger than window, it has scroll bar
            Fixed
        };

        ScrollView();
        ScrollView(ResizeMode mode);
                
        // ofxComponentBase
        void onStart() override;
        void onUpdate() override;
        void onDraw() override;
        
        void onMouseMoved(ofMouseEventArgs &mosue) override;
        void onMousePressed(ofMouseEventArgs &mosue) override;
        void onMouseDragged(ofMouseEventArgs &mosue) override;
        void onMouseReleased(ofMouseEventArgs &mosue) override;
        void onMouseScrolled(ofMouseEventArgs &mouse) override;
        void onLocalMatrixChanged() override;
        

        // ScrollView
        bool isHorizontalScrollEnabled() { return resizeMode == Fixed || resizeMode == Height;}
        bool isVerticalScrollEnabled() {return resizeMode == Fixed || resizeMode == Width;}
        
    private:
        
        ResizeMode resizeMode;

        // scroll bar
        void updateScrollBar();
        shared_ptr<ScrollBar> barV, barH;
    };
}
