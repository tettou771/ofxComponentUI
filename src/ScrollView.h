#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class ScrollBar : public ofxComponentBase {
    public:
        ScrollBar(){};
        void onDraw() override;
            
    private:
        //shared_ptr<ScrollView> parentScrollView;
    };

    class ScrollView : public View {
    public:
        ScrollView();

        // ofxComponentBase
        void onStart() override;
        void onUpdate() override;
        void onDraw() override;
        void onMouseMoved(ofMouseEventArgs& mosue) override;
        void onMousePressed(ofMouseEventArgs& mosue) override;
        void onMouseDragged(ofMouseEventArgs& mosue) override;
        void onMouseReleased(ofMouseEventArgs& mosue) override;
        void onMouseScrolled(ofMouseEventArgs& mouse) override;
        void onLocalMatrixChanged() override;

        // ScrollView
        void setScrollSpeed(float _speed);
        float getScrollSpeed() {return speed;}

        enum FitMode {
            None,
            FitWidth,
            FitHeight
        };
        
        void setFitMode(FitMode _mode);
        FitMode getFitMode() { return fitMode; }
        
    private:
        // scroll bar
        void scrollX(float x);
        void scrollY(float y);
        void updateScrollBar();
        shared_ptr<ScrollBar> barV, barH;
        bool barVDragging, barHDragging;

        // scroll speed
        float speed;

        FitMode fitMode;
    };
}
