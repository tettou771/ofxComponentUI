#pragma once
#include "ofxComponent.h"
#include "WindowComponent.h"

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
        enum FitMode {
            None,
            FitWidth,
            FitHeight
        };

        ScrollView();
        ScrollView(FitMode _mode);

        // ofxComponentBase
        void onStart() override;
        void onMouseMoved(ofMouseEventArgs& mosue) override;
        void onMousePressed(ofMouseEventArgs& mosue) override;
        void onMouseDragged(ofMouseEventArgs& mosue) override;
        void onMouseReleased(ofMouseEventArgs& mosue) override;
        void onMouseScrolled(ofMouseEventArgs& mouse) override;
        void onLocalMatrixChanged() override;
        void onDestroy() override;

        // hanlder
        void onContentsLocalMatrixChanged();

        // view
        void onSetContents() override;
        
        // ScrollView
        void setScrollSpeed(float _speed);
        float getScrollSpeed() {return speed;}
        
        void setFitMode(FitMode _mode);
        FitMode getFitMode() { return fitMode; }
        
        // scroll bar
        void scrollX(float x);
        void scrollY(float y);
        
    private:
        void updateScrollBar();
        shared_ptr<ScrollBar> barV, barH;
        bool barVDragging, barHDragging;

        // scroll speed
        float speed;

        FitMode fitMode;
        bool onContentsLocalMatrixChangedResistored = false;
    };
}
