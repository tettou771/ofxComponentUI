#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class StretchView : public View {
    public:
        enum Mode {
            NoCrop,
            Crop,
            Width,
            Height
        };

        StretchView();
        StretchView(Mode mode);
                
        // ofxComponentBase
        void onStart() override;
        void onLocalMatrixChanged() override;

        // StreatchView
        void setMode(Mode _mode);
        Mode getMode() { return mode; }

    private:
        Mode mode;
        void calcScale();
    };
}
